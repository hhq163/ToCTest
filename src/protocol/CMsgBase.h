#ifndef _CMSG_BASE_H_
#define _CMSG_BASE_H_

class CModule;

class CMsgBase
{
public:
    CMsgBase();
    virtual ~CMsgBase();

    virtual CMsgBase* Clone();

public:
    static int NewMsgFromBuf(uint8* pBuf, int32 &dwSize, CMsgBase** ppOutMsg);
    static int GetBufFromMsg(uint8* pBuf, int32 &dwSize, CMsgBase* pInMsg);
    static CMsgBase* NewMsg(uint16 wCmd);
    static void DelMsg(CMsgBase* pMsg);
    int GetEncryptType();
protected:
    virtual int Parse(uint8* pBuf, int32& dwSize);
    virtual int Pack(uint8* pBuf, int32& dwSize);
    void UpdateLen(uint8* pBuf, uint32 dwLen);

    int Encrypt(const char* src, uint32 srclen, char* des, uint32 deslen);
    int Decrypt(const char* src, uint32 srclen, char *& des, uint32 deslen);

public:
    //head
    uint32  m_dwLen;    /*包长度，包含包头*/
    uint16  m_wVer;     /*协议版本*/
    uint16  m_wCmd;     /*命令字*/
    uint32  m_dwSeqId;     /*包序号*/
    uint32  m_dwId; /*正常情况下是接收方ID，模块内部通信、用户心跳时是源模块ID，群聊时是群ID*/

    uint32  m_dwSessionId;/*session_id*/
    char*   m_pBuf;
    uint32  m_Buflen;
    uint16  m_wType;
    uint64  m_msgId;
    char*   m_pprotoBuf;
public:
    CModule* m_pRoute;
};

#endif
