#ifndef _UTIL_H
#define _UTIL_H

#include "Common.h"
#include <iconv.h>
#include <sys/syscall.h>
#include <zlib.h>

#include "Structs.h"
class CLock
{
public:
    CLock()
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

    ~CLock()
    {
        pthread_mutex_destroy(&m_mutex);
    }

public:
    inline void Lock()
    {
        pthread_mutex_lock(&m_mutex);
    }

    inline void UnLock()
    {
        pthread_mutex_unlock(&m_mutex);
    }

    inline pthread_mutex_t* GetHandle()
    {
        return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};

class CAutoLock
{
public:
    CAutoLock(pthread_mutex_t* mutex)
    {
        m_mutex = mutex;
        pthread_mutex_lock(m_mutex);
    }
    ~CAutoLock()
    {
        pthread_mutex_unlock(m_mutex);
    }

private:
    pthread_mutex_t* m_mutex;
};

//////////////////////////////////////////////////////////////////////////
class ITimer
{
public:
    ITimer() {};
    virtual ~ITimer() {};

    virtual void OnTimer(const uint32 dwID) = 0;
};

class CTimer
{
    typedef struct
    {
        ITimer*     pTimer;
        uint32      dwID;
        bool        bInto;
        timer_t     tid;
    }TIMER_INFO_t;

protected:
    CTimer();
public:
    virtual ~CTimer();

public:
    static CTimer* GetInstance();
    int SetTimer(ITimer* pTimer, uint32 dwID, uint32 dwSecond);
    void KillTimer(uint32 dwID);

protected:
    static void  OnHandle(union sigval v);

private:
    map<uint32, TIMER_INFO_t*>  m_mapTimers;
    static CTimer*              m_pInstance;
};


//////////////////////////////////////////////////////////////////////////
#ifndef CFG_OBJECT_POOL
template<typename T>
class CObjectPool
{
public:
    typedef list<T*> Elements;
    typedef typename list<T*>::iterator Iterator;
public:
    CObjectPool();
    virtual ~CObjectPool();

public:
    int     Init(int iMaxSize);
    void    Clear();
    int     SetObject(T* pInObj);
    int     GetObject(T** ppOutObj);

    int     GetNum();

private:
    Elements            m_stObjectQ;
    //pthread_mutex_t     m_Lock;
    CLock               m_oLock;
    uint32              m_dwMaxSize;
    uint32              m_dwMySize;
};

template<typename T>
CObjectPool<T>::CObjectPool()
{
    m_dwMaxSize = 0;
    m_dwMySize  = 0;
    //pthread_mutex_init(&m_Lock,NULL);
}

template<typename T>
CObjectPool<T>::~CObjectPool()
{
    Clear();
    //pthread_mutex_destroy(&m_Lock);
}

template<typename T>
void CObjectPool<T>::Clear()
{
    //CAutoLock lock(&m_Lock);
    CAutoLock lock(m_oLock.GetHandle());
    T* pObject = NULL;

    Iterator it = m_stObjectQ.begin();
    for (; it!= m_stObjectQ.end(); it++)
    {
        pObject = (T*)*it;
        delete pObject;
        pObject = NULL;
    }

    m_stObjectQ.clear();

}

template<typename T>
int CObjectPool<T>::Init(int iMaxSize)
{
    Clear();
    m_dwMaxSize = iMaxSize;
    m_dwMySize  = 0;
    return ERR_SUCCESS;
}

template<typename T>
int CObjectPool<T>::SetObject(T* pInObj)
{
    if (pInObj == NULL)
    {
        return ERR_FAILED;
    }

    //CAutoLock lock(&m_Lock);
    CAutoLock lock(m_oLock.GetHandle());
    //if(m_dwMySize >= m_dwMaxSize)
    //if(m_stObjectQ.size() >= m_dwMaxSize)
    //{
    //  Iterator it = m_stObjectQ.begin();
    //  T* p = (T*)*it;
    //  delete p;
    //  m_stObjectQ.erase(it);
    //  //  return ERR_NO_MORE_SPACE;
    //}
    m_stObjectQ.push_back(pInObj);
    m_dwMySize++;

    return ERR_SUCCESS;
}

template<typename T>
int CObjectPool<T>::GetObject(T** ppOutObj)
{
    //CAutoLock lock(&m_Lock);
    CAutoLock lock(m_oLock.GetHandle());
    Iterator it = m_stObjectQ.begin();
    if (m_stObjectQ.end() == it)
    {
        return ERR_FAILED;
    }

    *ppOutObj = (T*)*it;
    m_stObjectQ.erase(it);
    m_dwMySize--;

    return ERR_SUCCESS;
}

template<typename T>
int CObjectPool<T>::GetNum()
{
    //CAutoLock lock(&m_Lock);
    CAutoLock lock(m_oLock.GetHandle());
    //return m_stObjectQ.size();
    return m_dwMySize;
}

#else

typedef void (*CallbackDel)(void* pVoid);
template<typename T>
/**
 * 链表类，用于保存对象池
 */
class CObjectPool
{
    struct Node_t
    {
        T*      pData;
        Node_t* pNext;
    };

public:
    CObjectPool(CallbackDel cb = NULL);
    virtual ~CObjectPool();

public:
    int     Init(int iMaxSize);
    void    Clear();
    int     SetObject(T* pInObj);
    int     GetObject(T** ppOutObj);
    int     GetObjectAll(vector<T*>& ppOutObjList);
    T*      GetObjectByPos(uint32 pos);
    int     GetNum();

private:
    CallbackDel m_cbDel;
    Node_t      *m_pHead, *m_pTail, *m_pIdle;
    CLock       m_oLock;
    uint32      m_dwMaxSize;
    uint32      m_dwMySize;
};

template<typename T>
CObjectPool<T>::CObjectPool(CallbackDel cb /*= NULL*/):
m_cbDel(cb)
{
    m_pHead     = NULL;
    m_pTail     = NULL;
    m_pIdle     = NULL;
    m_dwMaxSize = 0;
    m_dwMySize  = 0;
}

template<typename T>
CObjectPool<T>::~CObjectPool()
{
    Clear();
}

template<typename T>
void CObjectPool<T>::Clear()
{
    CAutoLock lock(m_oLock.GetHandle());
    while (NULL != m_pHead)
    {
        Node_t* pCur = m_pHead;
        m_pHead = m_pHead->pNext;
        if (NULL == m_cbDel)
        {
        delete pCur->pData;
        }
        else
        {
            m_cbDel(pCur->pData);
        }
        delete pCur;
    }

    while (NULL != m_pIdle)
    {
        Node_t* pCur = m_pIdle;
        m_pIdle = m_pIdle->pNext;
        delete pCur;
    }

    m_pHead = m_pTail = m_pIdle = NULL;
    m_dwMySize = 0;
}

template<typename T>
int CObjectPool<T>::Init(int iMaxSize)
{
    Clear();
    m_dwMaxSize = iMaxSize;
    m_dwMySize  = 0;
    return ERR_SUCCESS;
}

template<typename T>
int CObjectPool<T>::SetObject(T* pInObj)
{
    if(pInObj == NULL)
    {
        return ERR_FAILED;
    }

    CAutoLock lock(m_oLock.GetHandle());
    /*if(m_dwMaxSize > 0 && m_dwMySize >= m_dwMaxSize)
    {
        Node_t* pCur   = m_pHead;
        m_pHead        = m_pHead->pNext;
        delete pCur->pData;
        pCur->pData    = pInObj;
        pCur->pNext    = NULL;
        m_pTail->pNext = pCur;
        m_pTail        = pCur;

        return ERR_SUCCESS;
    }*/

    Node_t* pCur = NULL;
    if (NULL == m_pIdle)
    {
        pCur = new Node_t();
    }
    else
    {
        pCur = m_pIdle;
        m_pIdle = m_pIdle->pNext;
    }
    pCur->pData  = pInObj;
    pCur->pNext  = NULL;

    if (NULL == m_pTail)
    {
        m_pHead = m_pTail = pCur;
    }
    else
    {
        m_pTail->pNext = pCur;
        m_pTail = pCur;
    }
    m_dwMySize++;

    return ERR_SUCCESS;
}

template<typename T>
int CObjectPool<T>::GetObject(T** ppOutObj)
{
    CAutoLock lock(m_oLock.GetHandle());
    if(NULL == m_pHead)
    {
        return ERR_FAILED;
    }

    *ppOutObj = (T*)m_pHead->pData;
    Node_t* pCur = m_pHead;
    if (m_pHead == m_pTail)
    {
        m_pHead = m_pTail = NULL;
    }
    else
    {
        m_pHead = m_pHead->pNext;
    }
    m_dwMySize--;

    pCur->pData = NULL;
    pCur->pNext = NULL;
    if (NULL == m_pIdle)
    {
        m_pIdle = pCur;
    }
    else
    {
        pCur->pNext = m_pIdle;
        m_pIdle = pCur;
    }

    return ERR_SUCCESS;
}


template<typename T>
int CObjectPool<T>::GetObjectAll(vector<T*>& ppOutObjList)
{
    CAutoLock lock(m_oLock.GetHandle());
    if(NULL == m_pHead)
    {
        return ERR_FAILED;
    }

    while ( NULL != m_pHead)
    {
        ppOutObjList.push_back((T*)m_pHead->pData);
        Node_t* pCur = m_pHead;
        if (m_pHead == m_pTail)
        {
            m_pHead = m_pTail = NULL;
        }
        else
        {
            m_pHead = m_pHead->pNext;
        }
        m_dwMySize--;

        pCur->pData = NULL;
        pCur->pNext = NULL;
        if (NULL == m_pIdle)
        {
            m_pIdle = pCur;
        }
        else
        {
            pCur->pNext = m_pIdle;
            m_pIdle = pCur;
        }
    }
    return ERR_SUCCESS;
}

template<typename T>
T* CObjectPool<T>::GetObjectByPos(uint32  pos)
{
    CAutoLock lock(m_oLock.GetHandle());
    if( pos >  m_dwMySize ) {return NULL;}
    Node_t* pCur = m_pHead;
    while ( --pos > 0  ) {pCur = pCur->pNext;}

    T* ppOutObj = (T*)pCur->pData;
    return ppOutObj;
}


template<typename T>
int CObjectPool<T>::GetNum()
{
    //CAutoLock lock(m_oLock.GetHandle());
    return m_dwMySize;
}

template<typename T>
class CObjectPooLockFree
{
    struct Node_t
    {
        T*      pData;
        Node_t* pNext;
    };

public:
    CObjectPooLockFree(CallbackDel cb = NULL);
    virtual ~CObjectPooLockFree();

public:
    int     Init(int iMaxSize);
    void    Clear();
    int     SetObject(T* pInObj);
    int     GetObject(T** ppOutObj);
    int     GetObjectAll(vector<T*>& ppOutObjList);
    T*      GetObjectByPos(uint32 pos);
    int     GetNum();

private:
    CallbackDel m_cbDel;
    Node_t      *m_pHead, *m_pTail;
    uint32      m_dwMaxSize;
    uint32      m_dwMySize;
};

template<typename T>
CObjectPooLockFree<T>::CObjectPooLockFree(CallbackDel cb /*= NULL*/):
m_cbDel(cb)
{
    m_pHead     = m_pTail = new Node_t();
    m_pHead->pNext = NULL;
    m_dwMaxSize = 0;
    m_dwMySize  = 0;
}

template<typename T>
CObjectPooLockFree<T>::~CObjectPooLockFree()
{
    Clear();
    delete m_pHead;
}

template<typename T>
void CObjectPooLockFree<T>::Clear()
{
    while (m_pTail != m_pHead)
    {
        Node_t* pCur = m_pHead;
        m_pHead = m_pHead->pNext;
        if (NULL == m_cbDel)
        {
        delete pCur->pData;
        }
        else
        {
            m_cbDel(pCur->pData);
        }
        delete pCur;
    }
    m_dwMySize = 0;
}

template<typename T>
int CObjectPooLockFree<T>::Init(int iMaxSize)
{
    Clear();
    m_dwMaxSize = iMaxSize;
    m_dwMySize  = 0;
    return ERR_SUCCESS;
}

template<typename T>
int CObjectPooLockFree<T>::SetObject(T* pInObj)
{
    if (pInObj == NULL)
    {
        return ERR_FAILED;
    }

    Node_t* pCur = NULL;
    pCur = new Node_t();
    pCur->pData  = NULL;
    pCur->pNext  = NULL;

    m_pTail->pNext = pCur;
    m_pTail->pData = pInObj;
    m_pTail = pCur;

    __sync_fetch_and_add(&m_dwMySize,1);

    return ERR_SUCCESS;
}

template<typename T>
int CObjectPooLockFree<T>::GetObject(T** ppOutObj)
{
    if (m_pTail == m_pHead)
    {
        return ERR_FAILED;
    }

    Node_t* pCur = m_pHead;
    *ppOutObj = (T*)pCur->pData;
    m_pHead = pCur->pNext;
    __sync_sub_and_fetch(&m_dwMySize,1);
    delete pCur;
    return ERR_SUCCESS;
}

template<typename T>
int CObjectPooLockFree<T>::GetObjectAll(vector<T*>& ppOutObjList)
{
    if (m_pTail == m_pHead)
    {
        return ERR_FAILED;
    }

    while ( m_pTail != m_pHead)
    {
        Node_t* pCur = m_pHead;
        ppOutObjList.push_back((T*)pCur->pData);
        m_pHead = pCur->pNext;
        __sync_sub_and_fetch(&m_dwMySize,1);
        delete pCur;
    }
    return ERR_SUCCESS;
}

template<typename T>
T* CObjectPooLockFree<T>::GetObjectByPos(uint32  pos)
{
    if ( 0 == pos || NULL == m_pHead || pos >  m_dwMySize )
    {
        return NULL;
    }
    Node_t* pCur = m_pHead;
    while ( --pos > 0 &&  pCur )
    {
        pCur = pCur->pNext;
    }
    if ( pCur )
    {
        T* ppOutObj = (T*)pCur->pData;
        return ppOutObj;
    }
    return NULL;
}


template<typename T>
int CObjectPooLockFree<T>::GetNum()
{
    return m_dwMySize;
}
#endif


//////////////////////////////////////////////////////////////////////////
/**
 * 信息号量操作类
 */
class CSem
{
public:
    CSem();
    ~CSem();

public:
    int Wait();
    int timedwait();
    int Post();
    int  GetValue();

private:
    sem_t *m_sem;
};

//////////////////////////////////////////////////////////////////////////
class CTask
{
public:
    CTask(){};
    virtual ~CTask(){};

public:
    FunCallback m_fCallback;
};

//////////////////////////////////////////////////////////////////////////
class CThreadPool;
/**
 * 线程管理类
 */
class CThread
{
public:
    CThread(CThreadPool* pThreadPool);
    virtual ~CThread();

public:
    bool Start();
    bool Stop();

    void AddTask(CTask* pTask);

protected:
    int Run();
    static void* Callback(void* pParam);

private:
    pthread_t       m_threadid;
    CThreadPool*    m_pThreadPool;
    CTask*          m_pTask;
    CSem            m_oSem;
    bool            m_bExit;
};

/**
 * 线程池管理类
 */
class CThreadPool
{
public:
    CThreadPool();
    virtual ~CThreadPool();

public:
    bool    Init(uint32 dwThreadNum, uint16 wFlag);
    uint16  GetFlag() {return m_wFlag;}
    void    PushThread(CThread* pThread);
    void    SubmitTask(CTask* pTask);
    void    CancelTask(uint16 iState);
    int     GetTaskCount() {return m_oTaskQ.GetNum();}
    int     GetThreadCount() {return m_oThreadQ.GetNum();}

private:
    uint16                  m_wFlag;
    CObjectPool<CThread>    m_oThreadQ;
    CObjectPool<CTask>      m_oTaskQ;
};


uint64 getkey(const char* key);
char* intip2char(int intip);
int LoadFilterKeyWords(string& strFilterWords);
int FilterKeyWords(uint8* pKeyWords, uint32 dwKeyLen, uint8* pContent, uint32 pContentLen);

int GbkToUtf8(char * sIn, size_t iInLen,char * sOut, size_t iMaxOutLen);
int Utf8ToGbk(char * sIn, size_t iInLen,char * sOut, size_t iMaxOutLen);
string ChangeToGbk(string sUtf);
string ChangeToUtf(string  sGbk);
char *s_iconv(const char *fromStr, const int fromLen, char**toStr, const char *fromCode, const char *toCode);
string s_gbk2utf8(const char*s);
string s_utf82gbk(const char*s);


string ChangeToUtf_2(string sGbk);
string Changeg2u(string sGbk);
string Changeun2u(string sGbk);

void get_memoccupy (MEM_OCCUPY *mem);
void get_cpuoccupy (CPU_OCCUPY *cpust);

inline string getCmdDesc(uint16 wCmd)
{
    switch (wCmd & ~CMD_INNER_FLAGE)
    {
        //内部协议
        case CMD_SYS_MODULE_LOGIN:
            return "CMD_SYS_MODULE_LOGIN";

        case CMD_SYS_MODULE_LOGIN_ACK:
            return "CMD_SYS_MODULE_LOGIN_ACK"; //模块注册响应

        case CMD_SYS_HEART_BEAT  :
            return "CMD_SYS_HEART_BEAT"; //模块心跳

        case CMD_SYS_HEART_BEAT_ACK:
            return "CMD_SYS_HEART_BEAT_ACK"; //模块心跳响应

        case CMD_SYS_MODULE_LOGOUT:
            return "CMD_SYS_MODULE_LOGOUT"; //模块注销

        case CMD_SYS_USER_CLOSE:
            return "CMD_SYS_USER_CLOSE"; //关闭用户连接

        //客户端协议
        case CMD_USER_LOGIN:
            return "CMD_USER_LOGIN";  //用户登录

        case CMD_USER_LOGIN_ACK:
            return "CMD_USER_LOGIN_ACK";  //用户登录响应

        case CMD_USER_LOGOUT:
            return "CMD_USER_LOGOUT";  //用户注销

        case CMD_USER_LOGOUT_ACK:
            return "CMD_USER_LOGOUT_ACK";  //用户注销响应

        case CMD_USER_HEARTBEAT:
            return "CMD_USER_HEARTBEAT";  //用户心跳

        case CMD_USER_HEARTBEAT_ACK:
            return "CMD_USER_HEARTBEAT_ACK";  //心跳响应

        //群聊相关
        case CMD_MSG_GROUP_SEND:
            return "CMD_MSG_GROUP_SEND";

        case CMD_MSG_GROUP_SEND_ACK:
            return "CMD_MSG_GROUP_SEND_ACK";

        case CMD_CS_GROUP_USER_LIST_GET:
            return "CMD_CS_GROUP_USER_LIST_GET";

        case CMD_CS_GROUP_USER_LIST_GET_ACK:
            return "CMD_CS_GROUP_USER_LIST_GET_ACK";

        case CMD_MSG_GROUP_RECV:
           return "CMD_MSG_GROUP_RECV";

        case CMD_MSG_GROUP_RECV_ACK:
            return "CMD_MSG_GROUP_RECV_ACK";

        default:
            return "UNKNOW CMD";

    }

    return "ERROR CMD";
}

#endif

