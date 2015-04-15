/*
 * CMsgNotify.cpp
 */
#include "Common.h"
#include "Log.h"
#include "MsgNotify.pb.h"
#include "CMsgNotify.h"


#include "Common.pb.h"
using namespace yunquan;

CMsgNotify::CMsgNotify()
{
    m_dwNotifyType = 0;
    m_dwSessionId = 0;
}

CMsgNotify::~CMsgNotify()
{
	
}


int CMsgNotify::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(ERROR, "CGroupMsgSend::Parse(in)");

    int iErr = CMsgBase::Parse(pBuf, dwUsedSize);
    if(ERR_SUCCESS != iErr)
    {
        return iErr;
    }
    p += dwUsedSize;


    m_Buflen = m_dwLen - dwUsedSize;
    if( m_Buflen > MAX_BUFFER_SIZE )
    {
        Logger.Log(ERROR, "parse msg bodylen[%d] > MAX_BUFFER_SIZE[%d] ", m_Buflen, MAX_BUFFER_SIZE);
        return ERR_FAILED;
    }
    if( m_dwLen > (uint32)dwSize )
    {
        return ERR_NO_MORE_DATA;
    }

    /*        check if need  Decrypt , ver??    */
    int nRet = 0;
    char* pdata = NULL;
    if( 0 > ( nRet = CMsgBase::Decrypt((const char*)p, m_dwLen - dwUsedSize, pdata, m_Buflen)))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Decrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
    CHECK_IF_NULL(pdata);

//////////////////////////////////////////////////////////////////////////
    string strData(pdata, m_Buflen);

    MsgNotify *pMsg = new MsgNotify();
    pMsg->Clear();


    if (pMsg->ParseFromString(strData))
    {
        if(pMsg->has_notifytype())
        {
            m_dwNotifyType = pMsg->notifytype();
        }
        if(pMsg->has_sessionid())
        {
            m_dwSessionId = pMsg->sessionid();
        }

        Logger.Log(INFO, "cmd:[0x%04x] m_dwDesUid:[%lld] m_dwSessionId:[%d]", m_wCmd, m_dwId, m_dwSessionId);
    }
    else
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Json parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
//////////////////////////////////////////////////////////////////////////
    p += m_Buflen;

    dwSize = (int32)(p - pBuf );
    Logger.Log(ERROR, "CGroupMsgSend::Parse(out)");
    return ERR_SUCCESS;

}


int CMsgNotify::Pack(uint8* pBuf, int32& dwSize)
{
    Logger.Log(ERROR, "CGroupMsgSend::Pack(in)");
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    int iErr = CMsgBase::Pack(p, dwUsedSize);
    if(ERR_SUCCESS != iErr)
    {
        return iErr;
    }
    p += dwUsedSize;

////////////////////////////////////////////////////////////////
    /*  ProtocolBuffer pack */

    MsgNotify *pMsg = new MsgNotify();
    pMsg->Clear();

    pMsg->set_notifytype((E_NOTIF_TYPE)m_dwNotifyType);
    pMsg->set_sessionid(m_dwSessionId);

    string buff = "";
    pMsg->SerializeToString(&buff);
//    Logger.Log(INFO, "CGroupMsgSend cmd=0x%04x pChatMsg.sessionid=%d", m_wCmd, pChatMsg->sessionid());

///////////////////////////////////////////////////////////
    if( dwSize < dwUsedSize + (int)buff.size())
    {
        return ERR_NO_MORE_DATA;
    }

    int nRet = 0;
    if( 0 > ( nRet = CMsgBase::Encrypt((const char*)buff.c_str(), (uint32)buff.size(), (char*)p, dwSize-dwUsedSize )))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Encrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }

    p += nRet;
    dwSize = m_dwLen = (int32)(p - pBuf);
    UpdateLen(pBuf, dwSize);
    Logger.Log(ERROR, "CGroupMsgSend::Pack(out)");

    return ERR_SUCCESS;
}

