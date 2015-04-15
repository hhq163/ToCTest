/*
 * CCSGroupUserListGetAck.h
 *
 *  Created on: 2015年4月9日
 *      Author: hhq163
 */

#ifndef _PROTOCOL_CCSGROUPUSERLISTGETACK_H_
#define _PROTOCOL_CCSGROUPUSERLISTGETACK_H_

#include  "CMsgBase.h"

/*
 *
 */
class CCSGroupUserListGetAck : public CMsgBase{
public:
    CCSGroupUserListGetAck();
    virtual ~CCSGroupUserListGetAck();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);
public:
    map<uint64,uint64>  m_mapuidlist;
};

#endif /* SRC_PROTOCOL_CCSGROUPUSERLISTGETACK_H_ */
