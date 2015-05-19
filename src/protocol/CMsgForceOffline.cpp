/*
 * CMsgForceDown.cpp
 * 强制用户下线
 *  Created on: 2015年4月21日
 *      Author: kevent
 */
#include "Common.h"
#include "Log.h"
#include "UserForceOffline.pb.h"
#include "CMsgForceOffline.h"

CMsgForceOffline::CMsgForceOffline()
{
    m_wClientType = 0;
    m_msg = "";
}

CMsgForceOffline::~CMsgForceOffline()
{
    m_wClientType = 0;
}

int CMsgForceOffline::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(INFO, "CMsgForceOffline::Parse(in)");

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

    string strData(pdata, m_Buflen);
//////////////////////////////////////////////////////////////////////////

    UserForceOffline *pUserForceOffline = new UserForceOffline();
    pUserForceOffline->Clear();

    if (pUserForceOffline->ParseFromString(strData))
    {
        if(pUserForceOffline->has_clienttype())
        {
            m_wClientType = pUserForceOffline->clienttype();
        }

        if(pUserForceOffline->has_msg())
        {
            m_msg = (pUserForceOffline->msg());
        }

        /*  Internal use  */
        if( m_wCmd & CMD_INNER_FLAGE )
        {
            if(pUserForceOffline->has_sessionid())
            {
                m_dwSessionId = pUserForceOffline->sessionid();
            }
        }
        Logger.Log(ERROR, "cmd:[0x%04x], m_dwDesUid:[%lld], m_dwSessionId:[%d], m_msg:[%s]", \
            m_wCmd, m_dwId, m_dwSessionId, m_msg.c_str());
    } 
    else
    {  
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Json parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;  
    } 
//////////////////////////////////////////////////////////////////////////  
    p += m_Buflen;

    dwSize = (int32)(p - pBuf );
    Logger.Log(ERROR, "CMsgForceOffline::Parse(out)");
    return ERR_SUCCESS;
    
}


int CMsgForceOffline::Pack(uint8* pBuf, int32& dwSize)
{
    Logger.Log(ERROR, "CMsgForceOffline::Pack(in)");
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
    
    UserForceOffline *pUserForceOffline = new UserForceOffline();
    pUserForceOffline->Clear();

    pUserForceOffline->set_clienttype((E_CLIENT_TYPE)m_wClientType);
    pUserForceOffline->set_msg(m_msg);
    pUserForceOffline->set_sessionid(m_dwSessionId);

    string buff = "";
    pUserForceOffline->SerializeToString(&buff);
    Logger.Log(INFO, "CMsgUserLogin pUserLogin.sessionid=%d", pUserForceOffline->sessionid());
 
    Logger.Log(INFO, "login cmd[0x%04x] ", m_wCmd);
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
    Logger.Log(INFO, "CMsgForceOffline::Pack(out)");

    return ERR_SUCCESS;
}
