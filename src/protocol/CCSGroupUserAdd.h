/*
 * CCSGroupUserAdd.h
 *
 *  Created on: 2015年4月15日
 *      Author: hhq163
 */

#ifndef _PROTOCOL_CCSGROUPUSERADD_H_
#define _PROTOCOL_CCSGROUPUSERADD_H_

#include  "CMsgBase.h"

/*
 *
 */
class CCSGroupUserAdd : public CMsgBase{
public:
    CCSGroupUserAdd();
    virtual ~CCSGroupUserAdd();
protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    map<uint64,uint64>  m_mapuidlist;
};

#endif /* SRC_PROTOCOL_CCSGROUPUSERADD_H_ */
