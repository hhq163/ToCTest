////////////////////////////////////////////////////////
//用户登录响应
#include "Common.h"
#include "Log.h"
#include "UserLoginAck.pb.h"
#include "CMsgUserLoginAck.h"


CMsgUserLoginAck::CMsgUserLoginAck()
{
    m_wRcode = 0;
    m_msg = "";
}

CMsgUserLoginAck::~CMsgUserLoginAck()
{

}

/**
 * parse package
 */
int CMsgUserLoginAck::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(ERROR, "CMsgUserLoginAck::Parse(in) dwSize=%d", dwSize);

    int iErr = CMsgBase::Parse(pBuf, dwUsedSize);
    if(ERR_SUCCESS != iErr)
    {
        return iErr;
    }
    p += dwUsedSize;

    Logger.Log(ERROR, "CMsgUserLoginAck::Parse222 dwSize=%d, m_dwLen=%d", dwSize, m_dwLen);

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

    /*
        check if need  Decrypt , ver??
    */

    int nRet = 0;
    char* pdata = NULL;
    if( 0 > ( nRet = CMsgBase::Decrypt((const char*)p, m_dwLen - dwUsedSize, pdata, m_Buflen)))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:%lld Decrypt failed", m_wCmd,  m_dwId);
        return ERR_FAILED;
    }
    CHECK_IF_NULL(pdata);

    string strData(pdata, m_Buflen);
//////////////////////////////////////////////////////////////////////////

    UserLoginAck *pAck = new UserLoginAck();
    pAck->Clear();

    if (pAck->ParseFromString(strData))
    {
        if(pAck->has_result())
        {
            m_wRcode = pAck->result();
        }

        if(pAck->has_msg())
        {
            m_msg = pAck->msg();
        }

        if(pAck->has_sessionid())
        {
            m_dwSessionId = pAck->sessionid();
        }

        if(pAck->has_name())
        {
              m_name = pAck->name();
        }

        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:[%d] m_wRcode:[%d] m_msg:[%s], m_dwSessionId:[%d]", \
            m_wCmd, m_dwId, m_wRcode, m_msg.c_str(), m_dwSessionId);
    }
    else
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:%d proto parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
//////////////////////////////////////////////////////////////////////////  
    p += m_Buflen;

    dwSize = (int32)(p - pBuf);
    Logger.Log(ERROR, "CMsgUserLoginAck::Parse(out)");
    return ERR_SUCCESS;

}

/**
 * pack package
 */
int CMsgUserLoginAck::Pack(uint8* pBuf, int32& dwSize)
{
    
    Logger.Log(ERROR, "CMsgUserLoginAck::Pack(in)");
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
    
    UserLoginAck *pAck = new UserLoginAck();
    pAck->Clear();

    pAck->set_result((E_RESULT)m_wRcode);
    pAck->set_msg(m_msg);
    pAck->set_name(m_name);

    /* Internal use */
    if( m_wCmd & CMD_INNER_FLAGE )
    {
        pAck->set_sessionid(m_dwSessionId);
    }

    string buff = "";
    pAck->SerializeToString(&buff);

    /*  Internal use    */

    if( dwSize < dwUsedSize + (int)buff.size())
    {
        return ERR_NO_MORE_DATA;
    }
    Logger.Log(INFO, "CMsgUserLoginAck::Pack cmd:[0x%04x] m_dwId:%d  m_dwSessionId:%d m_wRcode:%d",
            m_wCmd, m_dwId, m_dwSessionId, m_wRcode);

    int nRet = 0;
    if( 0 > ( nRet = CMsgBase::Encrypt((const char*)buff.c_str(), (uint32)buff.size(), (char*)p, dwSize-dwUsedSize )))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:%lld Encrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }

    p += nRet;

    dwSize = m_dwLen = dwUsedSize + buff.size();

    UpdateLen(pBuf, dwSize);
    Logger.Log(ERROR, "CMsgUserLoginAck::Pack(out)");

    return ERR_SUCCESS;
}

