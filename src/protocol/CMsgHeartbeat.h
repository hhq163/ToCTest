/*
 * CMsgHeartbeat.h
 */

#ifndef _PROTOCOL_CMSGHEARTBEAT_H_
#define _PROTOCOL_CMSGHEARTBEAT_H_

#include  "CMsgBase.h"

class CMsgHeartbeat : public CMsgBase
{
public:
    CMsgHeartbeat();
    virtual ~CMsgHeartbeat();

//protected:
//    virtual int Parse(uint8* pBuf, int32& dwSize);
//    virtual int Pack(uint8* pBuf, int32& dwSize);

//public:
//    uint32  m_dwStep;   //心跳间隔
//    uint64  m_llTotal;
//    uint64  m_llFree;
};

#endif
