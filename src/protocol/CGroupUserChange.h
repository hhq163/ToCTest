/*
 * CGroupUserChange.h
 *
 *  Created on: 2015年4月16日
 *      Author: hhq163
 */

#ifndef _PROTOCOL_CGROUPUSERCHANGE_H_
#define _PROTOCOL_CGROUPUSERCHANGE_H_

#include  "CMsgBase.h"

/*
 * 群聊成员变更
 */
class CGroupUserChange : public CMsgBase {
public:
    CGroupUserChange();
    virtual ~CGroupUserChange();
protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);
public:
    map<uint64,uint64>  m_mapuidlist;
};

#endif /* SRC_PROTOCOL_CGROUPUSERCHANGE_H_ */
