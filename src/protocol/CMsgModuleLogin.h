/*
 * CMsgModuleLogin.h
 * 模块注册
 */

#ifndef _PROTOCOL_CMSGMODULELOGIN_H_
#define _PROTOCOL_CMSGMODULELOGIN_H_

#include  "CMsgBase.h"

class CMsgModuleLogin : public CMsgBase
{
public:
    CMsgModuleLogin();
    virtual ~CMsgModuleLogin();

protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);

public:
    MODULE_INFO_t m_stModuleInfo;
};

#endif
