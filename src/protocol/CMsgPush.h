/*
 * CMsgPush.h
 *
 *  Created on: 2015年4月20日
 *      Author: kevent
 */

#ifndef _PROTOCOL_CMSG_PUSH_H_
#define _PROTOCOL_CMSG_PUSH_H_


#include"CMsgBase.h"


typedef struct MSG_ARRAY_T
{
    uint8* pMsg;
    uint32  len;
}MsgArray_t;

class CMsgPush : public CMsgBase
{
public:
    CMsgPush();
    virtual ~CMsgPush();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    MSG_ARRAY_T* NewMsgArray(int32 dwSize);

    MSG_ARRAY_T*  m_MsgArray[PAGE_SIZE];
    int32   m_dwMsgCount;
    MSG_ARRAY_T* tmp;
};



#endif /* IM_SANJIAODI_SRC_PROTOCOL_CMSGPUSH_H_ */
