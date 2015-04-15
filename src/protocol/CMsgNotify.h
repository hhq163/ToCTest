/*
 * CMsgNotify.h
 *
 */

#ifndef _PROTOCOL_CMSG_NOTIFY_H_
#define _PROTOCOL_CMSG_NOTIFY_H_

#include "Common.h"
#include "MsgObj.h"
#include "CMsgBase.h"

/*
 * 群聊消息
 */
class CMsgNotify : public CMsgBase {
public:
    CMsgNotify();
    virtual ~CMsgNotify();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    uint32 m_dwNotifyType;
};

#endif /* _PROTOCOL_CGROUPMSG_H_ */
