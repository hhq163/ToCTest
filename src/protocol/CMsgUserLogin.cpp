////////////////////////////////////////////////////////
//用户登录
#include "Common.h"
#include "Log.h"
#include "UserLogin.pb.h"
#include "CMsgUserLogin.h"

CMsgUserLogin::CMsgUserLogin()
{
    m_ClientId = "";
    m_ClientSecret = "";
    m_wClientType = 0;
}

CMsgUserLogin::~CMsgUserLogin()
{

}

int CMsgUserLogin::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(INFO, "CMsgUserLogin::Parse(in)");

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
    #if 1
    int nRet = 0;
    char* pdata = NULL;
    if( 0 > ( nRet = CMsgBase::Decrypt((const char*)p, m_dwLen - dwUsedSize, pdata, m_Buflen)))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Decrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
    CHECK_IF_NULL(pdata);
#endif
    string strData(pdata, m_Buflen);
//////////////////////////////////////////////////////////////////////////

    UserLogin *pUserLogin = new UserLogin();
    pUserLogin->Clear();

    if (pUserLogin->ParseFromString(strData))
    {
        if(pUserLogin->has_clienttype())
        {
            m_wClientType = pUserLogin->clienttype();
        }

        if(pUserLogin->has_clientid())
        {
            m_ClientId = pUserLogin->clientid();
        }
        if(pUserLogin->has_clientsecret())
        {
            m_ClientSecret = (pUserLogin->clientsecret());
        }
        if(pUserLogin->has_sessionid())
        {
            m_dwSessionId = pUserLogin->sessionid();
        }

        Logger.Log(ERROR, "cmd:[0x%04x], m_dwDesUid:[%lld], m_dwSessionId:[%d], m_ClientId:[%s], m_ClientSecret:[%s]", \
            m_wCmd, m_dwId, m_dwSessionId, m_ClientId.c_str(), m_ClientSecret.c_str());


        /*        Internal use            */
        if( m_wCmd & CMD_INNER_FLAGE )
        {

        }

    } 
    else
    {  
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Json parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;  
    } 
//////////////////////////////////////////////////////////////////////////  
    p += m_Buflen;
    
    dwSize = (int32)(p - pBuf );
    Logger.Log(ERROR, "CMsgUserLogin::Parse(out)");
    return ERR_SUCCESS;
    
}


int CMsgUserLogin::Pack(uint8* pBuf, int32& dwSize)
{
    Logger.Log(ERROR, "CMsgUserLogin::Pack(in)");
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

    UserLogin *pUserLogin = new UserLogin();
    pUserLogin->Clear();

    pUserLogin->set_clienttype((E_CLIENT_TYPE)m_wClientType);
    pUserLogin->set_clientid(m_ClientId);
    pUserLogin->set_clientsecret(m_ClientSecret);
    pUserLogin->set_sessionid(m_dwSessionId);
    //pUserLogin->PackToArray();


    string buff = "";
    //char buffer[1024] = {'\0'};
    //pAck->PackToArrary(buffer, m_Buflen );
    pUserLogin->SerializeToString(&buff);
    Logger.Log(INFO, "CMsgUserLogin pUserLogin.sessionid=%d", pUserLogin->sessionid());

    Logger.Log(INFO, "login cmd[0x%04x] ", m_wCmd);
///////////////////////////////////////////////////////////
    if( dwSize < dwUsedSize + (int)buff.size())
    {
        return ERR_NO_MORE_DATA;
    }

    int nRet = 0;
    if( 0 > ( nRet = CMsgBase::Encrypt((const char*)buff.c_str(), (uint32)buff.size(), (char*)p, dwSize-dwUsedSize )))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%u Encrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
    p += nRet;


    dwSize = m_dwLen = (int32)(p - pBuf);
    UpdateLen(pBuf, dwSize);

    if(NULL != pUserLogin)
    {
        delete pUserLogin;
        pUserLogin = NULL;
    }

    Logger.Log(INFO, "CMsgUserLogin::Pack(out)");

    return ERR_SUCCESS;
}

