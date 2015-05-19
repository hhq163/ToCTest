/*
 * CMsgHeartbeat.cpp
 */

#include "Common.h"
#include "CMsgHeartbeat.h"

CMsgHeartbeat::CMsgHeartbeat()
{
//    m_dwStep = 0;
    m_dwId = 0;
}

CMsgHeartbeat::~CMsgHeartbeat()
{

}
/*
int CMsgHeartbeat::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;

    int iErr = CMsgBase::Parse(pBuf, dwUsedSize);
    if(ERR_SUCCESS != iErr)
        return iErr;
    p += dwUsedSize;

//    m_dwStep = ntohl(*((uint32*)p));
//    p += 4;
//
//    m_llTotal = ntohll(*((uint64*)p));
//    p += 8;
//    m_llFree= ntohll(*((uint64*)p));
//    p += 8;

    dwSize = (int32)(p - pBuf);

    return ERR_SUCCESS;
}

int CMsgHeartbeat::Pack(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    int iErr = CMsgBase::Pack(p, dwUsedSize);
    if(ERR_SUCCESS != iErr)
        return iErr;
    p += dwUsedSize;


//    *(uint32*)p = htonl(m_dwStep);
//    p += 4;
//
//    *(uint64*)p = htonll(m_llTotal);
//    p += 8;
//
//    *(uint64*)p = htonll(m_llFree);
//    p += 8;

    dwSize = m_dwLen = (int32)(p - pBuf);
    UpdateLen(pBuf, dwSize);

    return ERR_SUCCESS;
}
*/
