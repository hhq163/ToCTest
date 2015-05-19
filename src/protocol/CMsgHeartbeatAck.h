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
};

#endif
