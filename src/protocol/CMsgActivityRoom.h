/*
 * CMsgActivityRoom.h
 *
 *  Created on: 2015年5月11日
 *      Author: Michael
 */

#ifndef _PROTOCOL_CMSG_ACTIVITY_ROOM_H_
#define _PROTOCOL_CMSG_ACTIVITY_ROOM_H_

#include"CMsgBase.h"
#include "ActivityRoom.pb.h"

class CMsgActivityRoom : public CMsgBase
{
public:
    CMsgActivityRoom();
    virtual ~CMsgActivityRoom();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    uint32  m_dwActivityID;

};



#endif /* _PROTOCOL_CMSG_ACTIVITY_ROOM_H_ */
