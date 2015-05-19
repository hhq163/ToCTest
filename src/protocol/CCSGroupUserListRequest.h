/*
 * CCSGroupUserListRequest.h
 *
 *  Created on: 2015年4月9日
 *      Author: hhq163
 */

#ifndef _PROTOCOL_CCSGROUPUSERLISTGET_H_
#define _PROTOCOL_CCSGROUPUSERLISTGET_H_

#include  "CMsgBase.h"

/*
 *
 */
class CCSGroupUserListRequest : public CMsgBase{
public:
    CCSGroupUserListRequest();
    virtual ~CCSGroupUserListRequest();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

};

#endif /* SRC_PROTOCOL_CCSGROUPUSERLISTGET_H_ */
