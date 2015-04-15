/*
 * CMsgHeartbeatAck.h
 */

#ifndef _PROTOCOL_CMSGHEARTBEATACK_H_
#define _PROTOCOL_CMSGHEARTBEATACK_H_

#include  "CMsgBase.h"

class CMsgHeartbeatAck : public CMsgBase
{
public:
    CMsgHeartbeatAck();
    virtual ~CMsgHeartbeatAck();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    uint16  m_wRcode;
};

#endif
