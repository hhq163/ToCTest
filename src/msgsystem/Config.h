#ifndef _CONFIG_H
#define _CONFIG_H

#include "Common.h"

/**
 * 配置类
 */
class CConfig
{
public:
    CConfig();
    virtual ~CConfig();

public:
    int ArgsParse(int argc, char **argv);
    bool Load();

private:
//    bool Load(const char* pFileName);
    bool Parse(string& strLine, string& strName, string& strValue);
    string& replace_all_distinct(string& str,const string& old_value,const string& new_value);

public:
    //host byte
    uint32  m_dwID;
    uint32  m_dwHostIp; //本机IP
    uint16  m_wHostPort; //本机用于处理长连接通信的端口

    uint16  m_wWebSvrPort; //本机用于处理web请求的Socket端口
    uint32  m_dwWebIp; //后端服务器端IP
    uint16  m_wWebPort; //后端服务器端口号

    string  m_strHttpApiHead; //Web接口Head
    string  m_strHttpApiUrl; //Web接口地址
    string  m_strEmailAddress; //httpheader解析异常时需要通知的邮箱
    int  m_wLogLevel;  //日志打印级别；
};

extern CConfig g_oConfig;

#endif

