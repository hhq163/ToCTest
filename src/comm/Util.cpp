#include "Util.h"
#include "Log.h"
#include "vsha256.h"

//////////////////////////////////////////////////////////////////////////
/**
 * 定时器
 */
CTimer* CTimer::m_pInstance = NULL;
CTimer::CTimer()
{

}

CTimer::~CTimer()
{
    map<uint32, TIMER_INFO_t*>::iterator it = m_mapTimers.begin();
    for (; it != m_mapTimers.end(); it++)
    {
        timer_delete(it->second->tid);
        delete it->second;
    }
    m_mapTimers.clear();
}

CTimer* CTimer::GetInstance()
{
    if (NULL == m_pInstance)
    {
        m_pInstance = new CTimer();
    }

    return m_pInstance;
}
/**
 * 设置定时器ID及间隔时间
 * uint32 dwID 定时器ID
 * uint32 dwSecond 间隔时间
 */
int CTimer::SetTimer(ITimer* pTimer, uint32 dwID, uint32 dwSecond)
{
    if (NULL == pTimer || dwID <= 0 || dwSecond <= 0)
    {
        return -1;
    }

    TIMER_INFO_t *pInfo = new TIMER_INFO_t;
    if (NULL == pInfo)
    {
        return -1;
    }
    memset(pInfo, 0, sizeof(TIMER_INFO_t));
    pInfo->pTimer   = pTimer;
    pInfo->dwID     = dwID;
    pInfo->bInto    = false;

    timer_t tid = 0;
    struct sigevent se;
    struct itimerspec ts, ots;
    memset(&se, 0, sizeof(struct sigevent));
    memset(&ts, 0, sizeof(struct itimerspec));
    memset(&ots, 0, sizeof(struct itimerspec));

    se.sigev_notify          = SIGEV_THREAD;
    se.sigev_notify_function = OnHandle;
    //  se.sigev_value.sival_int = uiID;   //作为handle()的参数
    se.sigev_value.sival_ptr = pInfo;
    //创建定时器
    if (timer_create(CLOCK_REALTIME, &se, &tid) < 0)
    {
        delete pInfo;
        pInfo = NULL;
        return   -1;
    }

    ts.it_value.tv_sec     = dwSecond;
    ts.it_value.tv_nsec    = 0;
    ts.it_interval.tv_sec  = dwSecond;
    ts.it_interval.tv_nsec = 0;
    //初始化定时器
    if (timer_settime(tid, TIMER_ABSTIME, &ts, &ots) < 0)
    {
        delete pInfo;
        pInfo = NULL;

        timer_delete(tid);
        return -1;
    }

    KillTimer(dwID);
    pInfo->tid = tid;
    m_mapTimers[dwID] = pInfo;

    return dwID;
}

void CTimer::KillTimer(uint32 dwID)
{
    map<uint32, TIMER_INFO_t*>::iterator it = m_mapTimers.find(dwID);
    if (it != m_mapTimers.end())
    {
        timer_delete(it->second->tid);
        delete it->second;
        m_mapTimers.erase(it);
    }
}

void  CTimer::OnHandle(union sigval v)
{
    TIMER_INFO_t* pInfo = (TIMER_INFO_t*)v.sival_ptr;
    if (NULL != pInfo && !pInfo->bInto)
    {
        pInfo->bInto = true;
        pInfo->pTimer->OnTimer(pInfo->dwID);
        pInfo->bInto = false;
    }
}


//////////////////////////////////////////////////////////////////////////
CSem::CSem():
m_sem(NULL)
{
    m_sem = new sem_t;
    if (0 != sem_init(m_sem, 0, 0))
    {
        Logger.Log(ERROR, "sem_init failed");
    }
}


CSem::~CSem()
{
    if (0 != sem_destroy(m_sem))
    {
        Logger.Log(ERROR, "sem_destroy failed");
    }

    if (NULL != m_sem)
    {
        delete m_sem;
        m_sem = NULL;
    }
}


int CSem::Wait()
{
    return sem_wait(m_sem);
}


int CSem::timedwait()
{
    struct timespec ts;
    ts.tv_sec = time(NULL) + 1;   // 重点
    ts.tv_nsec = 0;
    return sem_timedwait(m_sem, &ts);
}


int CSem::Post()
{
    return sem_post(m_sem);
}


int CSem::GetValue()
{
    int iValue = 0;
    sem_getvalue(m_sem, &iValue);

    return iValue;
}

//////////////////////////////////////////////////////////////////////////
CThread::CThread(CThreadPool* pThreadPool):
m_pThreadPool(pThreadPool),
m_pTask(NULL)
{
    m_bExit = false;
    m_threadid = 0;
}


CThread::~CThread()
{
    m_pThreadPool   = NULL;
    m_pTask         = NULL;
}


bool CThread::Start()
{
    if (pthread_create(&m_threadid, NULL, Callback, (void*)this) != 0)
    {
        Logger.Log(ERROR, "pthread_create failed");

        return false;
    }

    return true;
}


bool CThread::Stop()
{
    m_bExit = true;
    m_oSem.Post();
    pthread_join(m_threadid, NULL);
    return true;
}


void CThread::AddTask(CTask* pTask)
{
    m_pTask = pTask;
    if (m_oSem.GetValue() <= 0)
    {
        m_oSem.Post();
    }
}


int CThread::Run()
{
    for (;;)
    {
        m_oSem.Wait();
        if (m_bExit)
        {
            break;
        }
        //printf("threadid = %d\r\n", m_threadid);
        if (NULL != m_pTask &&  m_pTask->m_fCallback )
        {
            m_pTask->m_fCallback((void*)m_pTask, m_pThreadPool->GetFlag());
            m_pTask = NULL;

            m_pThreadPool->PushThread(this);
        }
    }

    return 0;
}


void* CThread::Callback(void *pParam)
{
    CThread* pThread = (CThread*)pParam;
    if (NULL != pThread)
    {
        pThread->Run();
    }

    return (void*)NULL;
}


//////////////////////////////////////////////////////////////////////////
CThreadPool::CThreadPool()
{

}


CThreadPool::~CThreadPool()
{

}


bool CThreadPool::Init(uint32 dwThreadNum, uint16 wFlag)
{
    if (dwThreadNum <= 0)
    {
        return false;
    }
    m_wFlag = wFlag;

    for (uint32 i = 0; i < dwThreadNum; i++)
    {
        CThread* pThread = new CThread(this);
        if (NULL != pThread)
        {
            pThread->Start();
            m_oThreadQ.SetObject(pThread);
        }
    }

    return true;
}

void CThreadPool::PushThread(CThread* pThread)
{
    if (NULL == pThread)
    {
        return;
    }

    CTask* pTask = NULL;
    if (ERR_SUCCESS == m_oTaskQ.GetObject(&pTask) && NULL != pTask)
    {
        pThread->AddTask(pTask);
    }
    else
    {
        m_oThreadQ.SetObject(pThread);
    }
}

/**
 * 往线程池中提交一个任务
 */
void CThreadPool::SubmitTask(CTask* pTask)
{
    if (NULL == pTask)
    {
        return;
    }

    CThread* pThread = NULL;
    if (ERR_SUCCESS == m_oThreadQ.GetObject(&pThread) && NULL != pThread)
    {
        pThread->AddTask(pTask);
    }
    else
    {
        m_oTaskQ.SetObject(pTask);
    }
}

void CThreadPool::CancelTask(uint16 iState)
{

}


char* intip2char(int intip)
{
    in_addr addr = {0};
    addr.s_addr  = intip;
    return inet_ntoa(addr);
}


int LoadFilterKeyWords(string& strFilterWords)
{
    FILE *pFile = NULL;
    pFile  = fopen("./filterwords.txt", "r");
    if (NULL != pFile)
    {
        strFilterWords = ",";
        int ret = 0;
        char buf[1024] = {0};

        while ((ret = fread(buf, 1, 1023, pFile)) > 0)
        {
            buf[ret] = '\0';
            strFilterWords += buf;
        }
        strFilterWords += ",";
        fclose(pFile);
        Logger.Log(INFO, "filter words:%s", strFilterWords.c_str());
    }

    return 0;
}

int FilterKeyWords(uint8* pKeyWords, uint32 dwKeyLen, uint8* pContent, uint32 pContentLen)
{
    if (NULL == pKeyWords || 0 == dwKeyLen || NULL == pContent || 0 == pContentLen)
    {
        return -1;
    }
    bool isReset = false;
    char *p1 = NULL;
    char *p2 = NULL;
    char *pFind = NULL;
    p1 = (char*)pKeyWords;

    while (p1 < ((char*)pKeyWords + dwKeyLen))
    {
        p2 = strstr(p1, ",");
        if (NULL == p2)
        {
            break;
        }
        if (p1 != p2)
        {
            p2[0] = '\0';
            int keylen = p2 - p1;
            while (1)
            {
                pFind = strcasestr((char*)pContent, p1);
                if (NULL != pFind)
                {
                    for (int i = 0; i < keylen; i++)
                    {
                        pFind[i] = '*';
                        isReset = true;
                    }
                }
                else
                {
                    break;
                }
            }
            p2[0] = ',';
        }
        p1 = p2 + 1;
    }
    return isReset == false ? 0 : 1;
}


int GbkToUtf8(char * sIn,   size_t iInLen, char * sOut, size_t iMaxOutLen)
{
    size_t ret = 0;
    iconv_t cd;

    /* 可С库编的*/
    cd = iconv_open("utf-8", "gbk");
    if (cd == (iconv_t) - 1)
    {
        //fprintf(stderr, "ERROR: iconv_open: %s\n", strerror(errno));
        return -1;
    }
    ret = iconv(cd, &sIn, &iInLen, &sOut, &iMaxOutLen);
    if (ret == (size_t) - 1)
    {
        //fprintf(stderr, "iconv %s: %s", sIn, strerror(errno));
        iconv_close(cd);
        return -1;
    }

    iconv_close(cd);

    return iMaxOutLen;
}


int Utf8ToGbk(char * sIn,size_t iInLen,char * sOut,size_t iMaxOutLen)
{
    size_t ret;
    iconv_t cd;

    /* 可С库编的*/
    cd = iconv_open("gbk", "utf-8");
    if (cd == (iconv_t) - 1)
    {
        //fprintf(stderr, "ERROR: iconv_open: %s\n", strerror(errno));
        return -1;
    }


    ret = iconv(cd, &sIn, &iInLen, &sOut, &iMaxOutLen);
    if (ret == (size_t) - 1)
    {
        //fprintf(stderr, "iconv %s: %s", sIn, strerror(errno));
        return -1;
    }

    iconv_close(cd);

    sOut[iMaxOutLen] = 0;

    return iMaxOutLen;
}


string ChangeToGbk(string sUtf)
{
    if (sUtf.length() == 0)
    {
        return string("");
    }
    char szBuff[MAX_MSG_LEN] = {0};
    int iBuffLen = sizeof(szBuff);
    char inBuff[MAX_MSG_LEN * 2] = {0};
    strncpy(inBuff, sUtf.c_str(), MAX_MSG_LEN * 2 - 1);

    int iRet = Utf8ToGbk(inBuff, strlen(inBuff), szBuff, iBuffLen);
    if ((iRet < 0) || ((uint32)iRet >= sizeof(szBuff)))
    {
        szBuff[sizeof(szBuff) - 1] = 0;
    }
    else
    {
        szBuff[iRet] = 0;
    }

    return string(szBuff);
}


string ChangeToUtf(string  sGbk)
{
    if (sGbk.length() == 0)
    {
        return string("");
    }

    char szBuff[MAX_MSG_LEN * 2] = {0};
    int iBuffLen = sizeof(szBuff);

    char inBuff[MAX_MSG_LEN * 2] = {0};
    strncpy(inBuff, sGbk.c_str(), MAX_MSG_LEN * 2 - 1);
    int iRet =  GbkToUtf8(inBuff, strlen(inBuff), szBuff, iBuffLen);
    //int iRet =  GbkToUtf8(sGbk.c_str(),sGbk.length(), szBuff, iBuffLen);
    if ((iRet < 0) || ((uint32)iRet >= sizeof(szBuff)))
    {
        szBuff[sizeof(szBuff) - 1] = 0;
    }
    else
    {
        szBuff[iRet] = 0;
    }

    return string(szBuff);
}

//ctk_
char *s_iconv(const char *fromStr, const int fromLen, char**toStr,  const char *fromCode, const char *toCode)
{
    char *buffer;
    iconv_t cd;
    const char *inbuf = NULL;
    size_t inbytesleft = 0;
    char *outbuf = NULL;
    size_t outbytesleft = 0;
    int errorCode = 0;
    int bufferSize = 0;
    size_t ret = 0;
    int done = 0;

    if (fromStr==NULL || fromStr[0]=='\0' || fromLen <=0 )
    {
        return NULL;
    }
    if (fromCode==NULL || fromCode[0]=='\0' )
    {
        return NULL;
    }
    if (toCode==NULL || toCode[0]=='\0' )
    {
        return NULL;
    }

    memset(&cd, 0x00, sizeof(iconv_t));
    inbuf = fromStr;
    inbytesleft = fromLen;

    errorCode = 0;
    bufferSize = fromLen * 4 + 1;
    buffer = (char*)malloc(sizeof(char)*bufferSize);
    memset(buffer, 0x00, bufferSize);

    outbuf = buffer;
    outbytesleft = bufferSize;

    if ( (iconv_t)-1  == ( cd = iconv_open(toCode, fromCode) ) )
    {
        return NULL;
    }

    while ( inbytesleft >0 && done !=1 )
    {
        ret = iconv(cd, (char**)&inbuf, &inbytesleft, &outbuf, &outbytesleft);
        if ( (size_t)-1  == ret )
        {
            errorCode = errno;
            switch (errorCode)
            {
            case EILSEQ:
            {
                if ((outbuf<buffer+bufferSize) && (outbuf>=buffer))
                {
                    memcpy(outbuf, inbuf, 1);
                    outbuf += 1;
                    outbytesleft -= 1;
                    inbuf += 1;
                    inbytesleft -= 1;
                    if ( inbytesleft <= 0 )
                    {
                        break;
                    }
                }
                break;
            }

            case EINVAL:
            {
                done = 1;
                break;
            }

            case E2BIG:
            {
                done = 1;
                break;
            }

            default:
                done = 1;
                break;
            }
        }
    }
    if ( NULL != toStr)
    {
        *toStr = buffer;
    }
    iconv_close(cd);
    return buffer;
}


//
string s_gbk2utf8(const char*s)
{
    s = s ? s:"";
    char *utf8str = NULL;
    s_iconv(s, strlen(s), &utf8str, "gbk", "utf-8");
    std::string result("");
    if (utf8str != NULL)
    {
        result = utf8str;
        free(utf8str);
    }
    return result;
}

string s_utf82gbk(const char*s)
{
    s = s ? s:"";
    char *gbkstr = NULL;
    s_iconv(s, strlen(s), &gbkstr, "utf-8", "gbk");
    std::string result("");
    if (gbkstr!=NULL)
    {
        result = gbkstr;
        free(gbkstr);
    }
    return result;
}

void get_memoccupy (MEM_OCCUPY *mem)
{
    FILE *fd;
    char buff[256] = {0};
    MEM_OCCUPY *m;
    m=mem;

    fd = fopen ("/proc/meminfo", "r");

    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %lu", m->name, &m->total);
    memset(buff, 0, 256);

    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %lu", m->name2,&m->free);

    //fgets (buff, sizeof(buff), fd);
    //fgets (buff, sizeof(buff), fd);
    //sscanf (buff, "%s %u %s %u", m->name, &m->total, m->name2,&m->free);

    //fgets (buff, sizeof(buff), fd); //从fd文件中读取长度为buff的字符串再存到起始地址为buff这个空间里
    //sscanf (buff, "%s %u", m->name2, &m->free, m->name2);

    fclose(fd);     //关闭文件fd
}

void get_cpuoccupy (CPU_OCCUPY *cpust) //对无类型get函数含有一个形参结构体类弄的指针O
{
    FILE *fd;
    char buff[256];
    CPU_OCCUPY *cpu_occupy;
    cpu_occupy=cpust;

    fd = fopen ("/proc/stat", "r");
    fgets (buff, sizeof(buff), fd);

    sscanf (buff, "%s %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice, &cpu_occupy->system, &cpu_occupy->idle);

    fclose(fd);
}
