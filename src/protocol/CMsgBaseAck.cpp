/* 
CMsgBaseAck.cpp
*/

#include "Common.h"
#include "Log.h"
#include "CMsgBaseAck.h"

CMsgBaseAck::CMsgBaseAck():m_wRcode(0)
{
}

CMsgBaseAck::~CMsgBaseAck()
{
}

 
/**
 * 消息包解析
 */
int CMsgBaseAck::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;

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

    /*
        check if need  Decrypt , ver??
    */
    int nRet = 0;
    char* pdata = NULL;
    if( 0 > ( nRet = CMsgBase::Decrypt((const char*)p, m_dwLen - dwUsedSize, pdata, m_Buflen)))
    {
        Logger.Log(ERROR, "cmd:[0x%04x]  m_dwId:%lld Decrypt failed", m_wCmd,m_dwId);
        return ERR_FAILED;
    }
    CHECK_IF_NULL(pdata);

//////////////////////////////////////////////////////////////////////////
    string strData(pdata, m_Buflen);
    Ack *pAck = new Ack();
    pAck->Clear();

    if (pAck->ParseFromString(strData))
    {

        if(pAck->has_result())
        {
            m_wRcode = pAck->result();
        }

        if(pAck->has_msg())
        {
            m_msg = (pAck->msg());
        }
        if(pAck->has_sessionid())
        {
            m_dwSessionId = pAck->sessionid();
        }
        
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:[%lld] m_wRcode:[%d] m_msg:[%s]", \
            m_wCmd, m_dwId, m_wRcode, m_msg.c_str());
    }
    else
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:%lld Json parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
//////////////////////////////////////////////////////////////////////////  
    p += m_Buflen;

    dwSize = (int32)(p - pBuf);
    return ERR_SUCCESS;

}


int CMsgBaseAck::Pack(uint8* pBuf, int32& dwSize)
{
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
    
    Ack *pAck = new Ack();
    pAck->Clear();

    pAck->set_result((E_RESULT)m_wRcode);
    pAck->set_msg(m_msg);
    pAck->set_sessionid(m_dwSessionId);

    string buff = "";
    pAck->SerializeToString(&buff);

    /*  Internal use    */

    if( dwSize < dwUsedSize + (int)buff.size())
    {
        return ERR_NO_MORE_DATA;
    }
#if 1
    int nRet = 0;
    if( 0 > ( nRet = CMsgBase::Encrypt((const char*)buff.c_str(), (uint32)buff.size(), (char*)p, dwSize-dwUsedSize )))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:%lld Encrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }

    p += nRet;
#endif

    dwSize = m_dwLen = dwUsedSize + buff.size();

    UpdateLen(pBuf, dwSize);

    return ERR_SUCCESS;
}


