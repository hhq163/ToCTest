#include "Common.h"
//#include "ProtJsonGetValue.h"
#include "Log.h"
#include "CRoomMsg.h"

CRoomMsg::CRoomMsg():m_ref(1)
{
    pthread_mutex_init(&m_mutex , NULL);
    m_wType  = 1;//MT_BROADCAST;
#if 1
//#ifdef __CONNECT_SVR__
    pthread_mutex_init(&m_write_mutex , NULL);
    m_buf = NULL;
    m_buflen = 0;
    m_isSetbuf = 0;
    
    m_base64buf = NULL;
    m_base64buflen = 0;
    m_isbase64Setbuf = 0;
#endif

}

CRoomMsg::~CRoomMsg()
{
    pthread_mutex_destroy(&m_mutex);
#if 1
//#ifdef __CONNECT_SVR__

    pthread_mutex_destroy(&m_write_mutex);
    if( m_buf )
    {
        delete[] m_buf;
        m_buf = NULL;
    }
    if( m_base64buf )
    {
        delete[] m_base64buf;
        m_base64buf = NULL;
    }
#endif

}

CRoomMsg* CRoomMsg::Clone()
{
    __sync_fetch_and_add(&m_ref,1);
    Logger.Log(DEBUG, "debug CRoomMsg::Clone msg[%p] type[0x%04x] ref++ =%d",this, m_wCmd, m_ref);
    return this;
}

#if 1
//#ifdef __CONNECT_SVR__
int CRoomMsg::GetMsg(uint16 type, uint8*& p, uint32& len)
{
    switch(type)
    {
        case NO_ENCRYPT:
        {
            if( m_isSetbuf )
            {
                p   = (uint8*)m_buf;
                len = m_buflen;
                return ERR_SUCCESS;
            }
            CAutoLock oLock(&m_write_mutex);
            if( 0 == m_isSetbuf )
            {
                m_buflen = MAX_BUFFER_SIZE;

                if( NULL == m_buf )m_buf = new char[m_buflen];

                p = (uint8*)m_buf;
                m_wVer = PROTOCOL_VERSION_0x1001;
                int iErr =  CMsgBase::GetBufFromMsg(p, m_buflen, (CMsgBase*)this);
                if (ERR_SUCCESS != iErr)
                {
                    Logger.Log(ERROR, "Err msg[%p] type[0x%04x] GetBufFromMsg ret=%d",this, m_wCmd, iErr);
                    return ERR_FAILED;
                }
                m_isSetbuf = 1;
                len = m_buflen;
                return ERR_SUCCESS;
            }
            else
            {
                p = (uint8*)m_buf;
                len = m_buflen;
                return ERR_SUCCESS;
            }
            break;
        }
        
        case ENCRYPT_BASE64:
        {
            if( m_isbase64Setbuf )
            {
                p   = (uint8*)m_base64buf;
                len = m_base64buflen;
                return ERR_SUCCESS;
            }
            
            CAutoLock oLock(&m_write_mutex);
            if( 0 == m_isbase64Setbuf )
            {
                m_base64buflen = MAX_BUFFER_SIZE;

                if( NULL == m_base64buf )m_base64buf = new char[m_base64buflen];
                
                p = (uint8*)m_base64buf;
                m_wVer = PROTOCOL_VERSION_0x2001;
                int iErr =  CMsgBase::GetBufFromMsg(p, m_base64buflen, (CMsgBase*)this);
                if (ERR_SUCCESS != iErr)
                {
                    Logger.Log(ERROR, "Err msg[%p] type[0x%04x] GetBufFromMsg ret=%d",this, m_wCmd, iErr);
                    return ERR_FAILED;
                }
                m_isbase64Setbuf = 1;
                len = m_base64buflen;
                return ERR_SUCCESS;
            }
            else
            {
                p = (uint8*)m_base64buf;
                len = m_base64buflen;
                return ERR_SUCCESS;
            }
            break;
        }
        default:
        {
            Logger.Log(ERROR, "Err msg[%p] type[%p] GetBufFromMsg ret=-1",this, type);
            return ERR_FAILED;
        }
    }
    
    return ERR_FAILED;  
}

#endif

int CRoomMsg::Del()
{
    return __sync_sub_and_fetch(&m_ref,1);
}

void CRoomMsg::DelRoomMsg(CRoomMsg* pMsg)
{
    if(NULL == pMsg)return; 
    if( 0 == pMsg->Del() )
    {
        Logger.Log(DEBUG, "debug msg[%p] type[0x%04x]  ref =%d delete it", pMsg, pMsg->m_wCmd, pMsg->m_ref);
        delete pMsg;
    }   
}

