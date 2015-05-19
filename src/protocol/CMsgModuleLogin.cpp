/*
 * CMsgModuleLogin.cpp
 * 模块注册
 */

#include "Common.h"
#include "Log.h"
#include "ModuleLogin.pb.h"
#include "CMsgModuleLogin.h"

CMsgModuleLogin::CMsgModuleLogin()
{
    m_dwMid = 0;
    m_wType = 0;
}

CMsgModuleLogin::~CMsgModuleLogin()
{

}

int CMsgModuleLogin::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;

    int iErr = CMsgBase::Parse(pBuf, dwUsedSize);
    if(ERR_SUCCESS != iErr)
        return iErr;
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

    ModuleLogin *pModuleLogin = new ModuleLogin();
    pModuleLogin->Clear();

    if (pModuleLogin->ParseFromString(strData))
    {
        if(pModuleLogin->has_moduleid())
        {
            m_dwMid = pModuleLogin->moduleid();
        }
        if(pModuleLogin->has_moduletype())
        {
            m_wType = pModuleLogin->moduletype();
        }


        Logger.Log(INFO, "cmd:[0x%04x] m_dwMid:[%u] m_wType:[%d]", m_wCmd, m_dwMid, m_wType);


    }
    else
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld proto parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
//////////////////////////////////////////////////////////////////////////
    p += m_Buflen;

    dwSize = (int32)(p - pBuf );
    Logger.Log(ERROR, "CModuleLoginSend::Parse(out)");
    return ERR_SUCCESS;
}

int CMsgModuleLogin::Pack(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    int iErr = CMsgBase::Pack(p, dwUsedSize);
    if(ERR_SUCCESS != iErr)
        return iErr;
    p += dwUsedSize;

////////////////////////////////////////////////////////////////
    /*  ProtocolBuffer pack */

    ModuleLogin *pModuleLogin = new ModuleLogin();
    pModuleLogin->Clear();
    pModuleLogin->set_moduleid(m_dwMid);
    pModuleLogin->set_moduletype(m_wType);


    string buff = "";
    pModuleLogin->SerializeToString(&buff);
//    Logger.Log(INFO, "CMsgModuleLogin cmd=0x%04x pModuleLogin.sessionid=%d", m_wCmd, pModuleLogin->sessionid());

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

    if(NULL != pModuleLogin){
        delete pModuleLogin;
        pModuleLogin = NULL;
    }

    Logger.Log(INFO, "CModuleLoginSend::Pack(out)");

    return ERR_SUCCESS;
}

