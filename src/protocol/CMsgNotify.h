/*
 * CMsgNotify.h
 *
 */

#ifndef _PROTOCOL_CMSG_NOTIFY_H_
#define _PROTOCOL_CMSG_NOTIFY_H_

#include "Common.h"
#include "Push.pb.h"
#include "CMsgBase.h"
using namespace yunquan;

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
    uint32 m_dwMessageType; //消息类型 0:消息(透传给应用的消息体 ,android任务栏不提示,ios不推送apns) 1:通知（对应设备上的消息通知）
    uint32 m_dwpushType; //推送类型 1:单人 2:多人 3:所有人
    uint32 m_dwEventType; //事件类型
    map<uint32,uint32>  m_mapUidList;//uid列表
    uint64 m_llMessageExpires;//过期时间
    map<uint32, Push_Payload*> m_PayloadList;//消息列表
};

#endif /* _PROTOCOL_CGROUPMSG_H_ */
