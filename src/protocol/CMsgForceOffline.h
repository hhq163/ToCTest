/*
 * CMsgForceOffline.h
 * 强制用户下线
 *  Created on: 2015年4月21日
 *      Author: kevent
 */

#ifndef _PROTOCOL_CMSG_FORCE_OFFLINE_H_
#define _PROTOCOL_CMSG_FORCE_OFFLINE_H_

#include  "CMsgBase.h"

class CMsgForceOffline : public CMsgBase
{
public:
    CMsgForceOffline();
	virtual ~CMsgForceOffline();

protected:
	virtual int Parse(uint8* pBuf, int32& dwSize);
	virtual int Pack(uint8* pBuf, int32& dwSize);

public:
	uint16  m_wClientType;//客户端类型
	string  m_msg;  //文本消息
};

#endif
