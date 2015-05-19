/*
 * CMsgSync.h
 *
 *  Created on: 2015年4月17日
 *      Author: Michael
 */

#ifndef _PROTOCOL_CMSG_SYNC_H_
#define _PROTOCOL_CMSG_SYNC_H_

#include"CMsgBase.h"
#include "MsgSync.pb.h"

class CMsgSync : public CMsgBase
{
public:
	CMsgSync();
    virtual ~CMsgSync();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    uint64  m_llSyncKey;

};



#endif /* _PROTOCOL_CMSG_SYNC_H_ */
