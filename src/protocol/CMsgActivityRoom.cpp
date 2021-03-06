/*
 * CMsgActivityRoom.cpp
 *
 *  Created on: 2015年5月11日
 *      Author: Michael
 */


#include "Common.h"
#include "Log.h"
#include "CMsgActivityRoom.h"

CMsgActivityRoom::CMsgActivityRoom():m_dwActivityID(0)
{
}

CMsgActivityRoom::~CMsgActivityRoom()
{
}


/**
 * 消息包解析
 */
int CMsgActivityRoom::Parse(uint8* pBuf, int32& dwSize)
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
    ActivityRoom *pProtocolBuffer = new ActivityRoom();
    pProtocolBuffer->Clear();

    if (pProtocolBuffer->ParseFromString(strData))
    {

        if(pProtocolBuffer->has_activityid())
        {
            m_dwActivityID = pProtocolBuffer->activityid();
        }


        Logger.Log(ERROR, "cmd:[0x%04x] m_dwId:[%u] m_dwActivityID:[%llu]", \
            m_wCmd, m_dwId, m_dwActivityID);
    }
    else
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwId:%u protocol parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
//////////////////////////////////////////////////////////////////////////
    p += m_Buflen;

    dwSize = (int32)(p - pBuf);
    return ERR_SUCCESS;

}


int CMsgActivityRoom::Pack(uint8* pBuf, int32& dwSize)
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

    ActivityRoom *pProtocolBuffer = new ActivityRoom();
    pProtocolBuffer->Clear();
    pProtocolBuffer->set_activityid(m_dwActivityID);

    string buff = "";
    pProtocolBuffer->SerializeToString(&buff);

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





