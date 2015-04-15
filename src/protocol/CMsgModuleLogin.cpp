/*
 * CMsgModuleLogin.cpp
 * 模块注册
 */

#include "Common.h"
#include "Log.h"
#include "CMsgModuleLogin.h"

CMsgModuleLogin::CMsgModuleLogin()
{
    memset(&m_stModuleInfo, 0, sizeof(MODULE_INFO_t));
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

    m_stModuleInfo.dwMid = ntohl(*((uint32*)p));
    p += 4;
    m_stModuleInfo.wType = ntohs(*((uint16*)p));
    p += 2;
    m_stModuleInfo.dwIp = ntohl(*((uint32*)p));
    p += 4;
    m_stModuleInfo.wPort = ntohs(*((uint16*)p));
    p += 2;

    dwSize = (int32)(p - pBuf);

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

    int32 dwBodyLen = 4+2+4+2;
    if(dwSize-dwUsedSize < dwBodyLen)
        return ERR_NO_MORE_SPACE;

    *((uint32*)p) = htonl(m_stModuleInfo.dwMid);
    p += 4;
    *((uint16*)p) = htons(m_stModuleInfo.wType);
    p += 2;
    *((uint32*)p) = htonl(m_stModuleInfo.dwIp);
    p += 4;
    *((uint16*)p) = htons(m_stModuleInfo.wPort);
    p += 2;

    dwSize = m_dwLen = (int32)(p - pBuf);

    Logger.Log(ERROR, "CMsgModuleLogin::Pack dwSize=%d", dwSize);
    UpdateLen(pBuf, dwSize);

    return ERR_SUCCESS;
}

