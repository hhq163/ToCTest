/*
 CMsgBaseAck.h
*/

#ifndef _C_MSG_BASE_ACK_H_
#define _C_MSG_BASE_ACK_H_

#include"CMsgBase.h"
#include "Ack.pb.h"

class CMsgBaseAck : public CMsgBase
{
public:
    CMsgBaseAck();
    virtual ~CMsgBaseAck();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    uint16  m_wRcode;
    string  m_msg;
};

#endif
