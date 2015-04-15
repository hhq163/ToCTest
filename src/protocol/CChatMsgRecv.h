/*
 * CChatMsgRecv.h
 */

#ifndef _PROTOCOL_CCHAT_MSG_RECV_H_
#define _PROTOCOL_CCHAT_MSG_RECV_H_

#include  "Common.h"
#include  "MsgObj.h"
#include  "CRoomMsg.h"

/* chat msg recv */
class CChatMsgRecv : public CRoomMsg
{
public:
    CChatMsgRecv();
    virtual ~CChatMsgRecv();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:

    uint32 m_dwFromUid;
    uint64 m_llMsgId;
    time_t m_sendtime;
    uint32 m_dwObjType;
    MsgObjBase* m_MsgObjBase;
    string      m_txt;
};

#endif /* _PROTOCOL_CCHAT_MSG_RECV_H_ */
