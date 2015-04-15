////////////////////////////////////////////////////////
//用户登录响应
#ifndef _C_MSG_USER_LOGIN_ACK_H_
#define _C_MSG_USER_LOGIN_ACK_H_

#include  "CMsgBaseAck.h"

class CMsgUserLoginAck : public CMsgBaseAck
{
public:
    CMsgUserLoginAck();
    virtual ~CMsgUserLoginAck();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:

};

#endif
