/*
 * CMsgModuleLoginAck.cpp
 * 模块注册响应
 */

#include "Common.h"
#include "Log.h"
#include "ModuleLoginAck.pb.h"
#include "CMsgModuleLoginAck.h"

CMsgModuleLoginAck::CMsgModuleLoginAck()
{
    m_dwSrcMid = 0;
    m_wRcode = 0;
}

CMsgModuleLoginAck::~CMsgModuleLoginAck()
{

}

int CMsgModuleLoginAck::Parse(uint8* pBuf, int32& dwSize)
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

    ModuleLoginAck *pModuleLoginAck = new ModuleLoginAck();
    pModuleLoginAck->Clear();

    if (pModuleLoginAck->ParseFromString(strData))
    {
        if(pModuleLoginAck->has_result())
        {
            m_wRcode = pModuleLoginAck->result();
        }

        if(pModuleLoginAck->has_srcmid())
        {
            m_dwSrcMid = pModuleLoginAck->srcmid();
        }
        Logger.Log(INFO, "cmd:[0x%04x] m_dwSrcMid:[%u] m_wRcode:[%d]", m_wCmd, m_dwSrcMid, m_wRcode);


    }
    else
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld proto parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
//////////////////////////////////////////////////////////////////////////
    p += m_Buflen;

    dwSize = (int32)(p - pBuf );
    Logger.Log(ERROR, "ModuleLoginAck::Parse(out)");
    return ERR_SUCCESS;
}

int CMsgModuleLoginAck::Pack(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    int iErr = CMsgBase::Pack(p, dwUsedSize);
    if(ERR_SUCCESS != iErr)
        return iErr;
    p += dwUsedSize;

////////////////////////////////////////////////////////////////
    /*  ProtocolBuffer pack */

    ModuleLoginAck *pModuleLoginAck = new ModuleLoginAck();
    pModuleLoginAck->Clear();
    pModuleLoginAck->set_result(m_wRcode);
    pModuleLoginAck->set_srcmid(m_dwSrcMid);

    string buff = "";
    pModuleLoginAck->SerializeToString(&buff);

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

    if(NULL != pModuleLoginAck){
        delete pModuleLoginAck;
        pModuleLoginAck = NULL;
    }

    Logger.Log(INFO, "CModuleLoginAck::Pack(out)");

    return ERR_SUCCESS;
}
