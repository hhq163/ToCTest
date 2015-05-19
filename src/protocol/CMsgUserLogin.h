////////////////////////////////////////////////////////
//用户登录
#ifndef _C_MSG_USER_LOGIN_H_
#define _C_MSG_USER_LOGIN_H_

#include  "CMsgBase.h"

class CMsgUserLogin : public CMsgBase
{
public:
	CMsgUserLogin();
	virtual ~CMsgUserLogin();

protected:
	virtual int Parse(uint8* pBuf, int32& dwSize);
	virtual int Pack(uint8* pBuf, int32& dwSize);
public:
	uint16  m_wClientType;//客户端类型
	string  m_ClientId; //客户端ID,非uid
	string  m_ClientSecret;  //用户秘钥
};

#endif
