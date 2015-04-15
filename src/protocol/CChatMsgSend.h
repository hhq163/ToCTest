/*
 * CChatMsgSend.h
 */

#ifndef _PROTOCOL_CCHAT_MSG_SEND_H_
#define _PROTOCOL_CCHAT_MSG_SEND_H_

#include "Common.h"
#include "MsgObj.h"
#include "CMsgBase.h"

/* chat msg send */
class CChatMsgSend : public CMsgBase
{
public:
    CChatMsgSend();
    virtual ~CChatMsgSend();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    uint32 m_dwFromUid;
    uint64 m_llMsgId;
    time_t m_sendtime;
    uint32 m_dwObjType;
    MsgObjBase* m_MsgObjBase;
    string m_txt;
};

#endif /* _PROTOCOL_CCHAT_MSG_SEND_H_ */
