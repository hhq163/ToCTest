/*
 * CMsgUserLogout.cpp
 * 用户注销
 *  Created on: 2015年4月20日
 *      Author: kevent
 */
#include "Common.h"
#include "Log.h"
#include "UserLogout.pb.h"
#include "CMsgUserLogout.h"

CMsgUserLogout::CMsgUserLogout()
{
    m_wClientType = 0;
}

CMsgUserLogout::~CMsgUserLogout()
{
    m_wClientType = 0;
}

int CMsgUserLogout::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(INFO, "CMsgUserLogout::Parse(in)");

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
    UserLogout *pUserLogout = new UserLogout();
    pUserLogout->Clear();

    if (pUserLogout->ParseFromString(strData))
    {
        if(pUserLogout->has_clienttype())
        {
            m_wClientType = pUserLogout->clienttype();
        }
    } 
    else
    {  
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld protocl parse failed", m_wCmd, m_dwId);
        return ERR_FAILED;  
    } 
//////////////////////////////////////////////////////////////////////////  
    p += m_Buflen;
    
    dwSize = (int32)(p - pBuf );
    Logger.Log(ERROR, "CMsgUserLogout::Parse(out)");
    return ERR_SUCCESS;
    
}


int CMsgUserLogout::Pack(uint8* pBuf, int32& dwSize)
{
    Logger.Log(ERROR, "CMsgUserLogout::Pack(in)");
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
    
    UserLogout *pUserLogout = new UserLogout();
    pUserLogout->Clear();
    pUserLogout->set_clienttype((E_CLIENT_TYPE)m_wClientType);

    string buff = "";
    pUserLogout->SerializeToString(&buff);

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
    Logger.Log(INFO, "CMsgUserLogout::Pack(out)");

    return ERR_SUCCESS;
}
