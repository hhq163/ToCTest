/*
 * CMsgModuleLoginAck.h
 * 模块注册响应
 */

#ifndef _PROTOCOL_CMSGMODULELOGINACK_H_
#define _PROTOCOL_CMSGMODULELOGINACK_H_

#include "Common.h"
#include "CMsgBase.h"
/**
 * 模块注册响应
 */
class CMsgModuleLoginAck : public CMsgBase
{
public:
    CMsgModuleLoginAck();
    virtual ~CMsgModuleLoginAck();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    uint32  m_dwSrcMid;//源服务器ID
    uint16  m_wRcode;//返回码
};

#endif
