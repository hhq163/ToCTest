/*
 * CMsgHeartbeatAck.cpp
 */

#include "Common.h"
#include "CMsgHeartbeatAck.h"

CMsgHeartbeatAck::CMsgHeartbeatAck()
{
    m_wRcode = 0;
}

CMsgHeartbeatAck::~CMsgHeartbeatAck()
{

}

int CMsgHeartbeatAck::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;

    int iErr = CMsgBase::Parse(pBuf, dwUsedSize);
    if(ERR_SUCCESS != iErr)
        return iErr;
    p += dwUsedSize;

    m_wRcode = ntohs(*(uint16*)p);
    p += 2;

    dwSize = (int32)(p - pBuf);

    return ERR_SUCCESS;
}

int CMsgHeartbeatAck::Pack(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    int iErr = CMsgBase::Pack(p, dwUsedSize);
    if(ERR_SUCCESS != iErr)
        return iErr;
    p += dwUsedSize;

    *(uint16*)p = htons(m_wRcode);
    p += 2;

    dwSize = m_dwLen = (int32)(p - pBuf);
    UpdateLen(pBuf, dwSize);

    return ERR_SUCCESS;
}
