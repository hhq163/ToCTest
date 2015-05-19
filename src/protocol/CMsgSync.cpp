/*
 * CMsgSync.cpp
 *
 *  Created on: 2015年4月17日
 *      Author: Michael
 */


#include "Common.h"
#include "Log.h"
#include "CMsgSync.h"

CMsgSync::CMsgSync():m_llSyncKey(0)
{
}

CMsgSync::~CMsgSync()
{
}


/**
 * 消息包解析
 */
int CMsgSync::Parse(uint8* pBuf, int32& dwSize)
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
    MsgSync *pMsgSync = new MsgSync();
    pMsgSync->Clear();

    if (pMsgSync->ParseFromString(strData))
    {

        if(pMsgSync->has_synckey())
        {
            m_llSyncKey = pMsgSync->synckey();
        }


        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:[%lld] m_wRcode:[%llu]", \
            m_wCmd, m_dwId, m_llSyncKey);
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


int CMsgSync::Pack(uint8* pBuf, int32& dwSize)
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

    MsgSync *pMsgSync = new MsgSync();
    pMsgSync->Clear();


    pMsgSync->set_synckey(m_llSyncKey);

    string buff = "";
    pMsgSync->SerializeToString(&buff);

    /*  Internal use    */

    if( dwSize < dwUsedSize + (int)buff.size())
    {
        return ERR_NO_MORE_DATA;
    }

    int nRet = 0;
    if( 0 > ( nRet = CMsgBase::Encrypt((const char*)buff.c_str(), (uint32)buff.size(), (char*)p, dwSize-dwUsedSize )))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:%lld Encrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }

    p += nRet;

    dwSize = m_dwLen = dwUsedSize + buff.size();

    UpdateLen(pBuf, dwSize);

    return ERR_SUCCESS;
}





