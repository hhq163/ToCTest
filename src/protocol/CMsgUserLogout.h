/*
 * CMsgUserLogout.h
 * 用户注销
 *  Created on: 2015年4月20日
 *      Author: kevent
 */

#ifndef _PROTOCOL_CMSG_USER_LOGOUT_H_
#define _PROTOCOL_CMSG_USER_LOGOUT_H_


#include  "CMsgBase.h"

class CMsgUserLogout : public CMsgBase
{
public:
    CMsgUserLogout();
	virtual ~CMsgUserLogout();

protected:
	virtual int Parse(uint8* pBuf, int32& dwSize);
	virtual int Pack(uint8* pBuf, int32& dwSize);

public:
	uint16  m_wClientType;//客户端类型
	string  m_ClientId; //客户端ID,非uid
	string  m_ClientSecret;  //用户秘钥
};

#endif
