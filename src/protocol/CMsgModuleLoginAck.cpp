/*
 * CMsgModuleLoginAck.cpp
 * 模块注册响应
 */

#include "Common.h"
#include "Log.h"
#include "CMsgModuleLoginAck.h"

CMsgModuleLoginAck::CMsgModuleLoginAck()
{
    m_wCount = 0;
    m_dwSrcUid = 0;
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

    m_wRcode = ntohs(*(uint16*)p);
    p += 2;

    if (RET_REDIRECT == m_wRcode)
    {
        m_wCount = ntohs(*((uint16*)p));
        p += 2;
        for (uint16 i = 0; i < m_wCount; i++)
        {
            MODULE_INFO_t stModuleInfo = {0};
            stModuleInfo.dwMid = ntohl(*((uint32*)p));
            p += 4;
            stModuleInfo.wType = ntohs(*((uint16*)p));
            p += 2;
            stModuleInfo.dwIp = ntohl(*((uint32*)p));
            p += 4;
            stModuleInfo.wPort = ntohs(*((uint16*)p));
            p += 2;

            m_vecModuleInfo.push_back(stModuleInfo);
        }
    }

    dwSize = (int32)(p - pBuf);

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

    *(uint16*)p = htons(m_wRcode);
    p += 2;

    if (RET_REDIRECT == m_wRcode)
    {
        int32 dwBodyLen = m_wCount * sizeof(MODULE_INFO_t);
        if(dwSize - dwUsedSize < dwBodyLen)
        {
            Logger.Log(ERROR, "pack data, the buffer size:%d dwBodyLen[%u] ",\
                    dwSize, dwBodyLen);
            return ERR_NO_MORE_SPACE;
        }
        *(uint16*)p = htons(m_wCount);
        p += 2;


        for (uint16 i = 0; i < m_wCount; i++)
        {
            *((uint32*)p) = htonl(m_vecModuleInfo[i].dwMid);
            p += 4;
            *((uint16*)p) = htons(m_vecModuleInfo[i].wType);
            p += 2;
            *((uint32*)p) = htonl(m_vecModuleInfo[i].dwIp);
            p += 4;
            *((uint16*)p) = htons(m_vecModuleInfo[i].wPort);
            p += 2;
        }

    }

    dwSize = m_dwLen = (int32)(p - pBuf);
    UpdateLen(pBuf, dwSize);

    return ERR_SUCCESS;
}
