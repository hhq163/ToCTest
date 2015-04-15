/**
 * 圈子消息类定义
 */
#ifndef _C_ROOM_MSG_H_
#define _C_ROOM_MSG_H_

#include  "CMsgBase.h"

class CRoomMsg :public CMsgBase
{
public:
    CRoomMsg();
    virtual ~CRoomMsg();

    virtual CRoomMsg* Clone();
    virtual int Del();
    static void DelRoomMsg(CRoomMsg* pMsg);
#if 1
//#ifdef __CONNECT_SVR__
    int GetMsg(uint16 type, uint8*& p, uint32& len);
#endif

public:
    pthread_mutex_t         m_mutex;
    int                     m_ref;
#if 1
//#ifdef __CONNECT_SVR__
    pthread_mutex_t         m_write_mutex;
    char*                   m_buf;
    int32                   m_buflen;
    uint16                  m_isSetbuf;

    char*                   m_base64buf;
    int32                   m_base64buflen;
    uint16                  m_isbase64Setbuf;   
#endif  
};

#endif
