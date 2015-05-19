/*
 * CCSGroupUserListAck.h
 *
 *  Created on: 2015年4月9日
 *      Author: hhq163
 */

#ifndef _PROTOCOL_CCSGROUPUSERLISTGETACK_H_
#define _PROTOCOL_CCSGROUPUSERLISTGETACK_H_

#include  "CMsgBaseAck.h"

/*
 *
 */
class CCSGroupUserListAck : public CMsgBaseAck{
public:
    CCSGroupUserListAck();
    virtual ~CCSGroupUserListAck();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);
public:
    map<uint32,uint32>  m_mapuidlist;
};

#endif /* SRC_PROTOCOL_CCSGROUPUSERLISTGETACK_H_ */
