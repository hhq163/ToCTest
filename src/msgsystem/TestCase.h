/*
 * TestCase.h
 *
 *  Created on: 2015年4月15日
 *      Author: hhq163
 */

#ifndef _MSGSYSTEM_TESTCASE_H_
#define _MSGSYSTEM_TESTCASE_H_

/*
 * 测试用例
 */
class TestCase {
public:
    TestCase();
    virtual ~TestCase();

    int UserLogin();
    int GroupMsgSend(CLIENT_INFO_T* client);//群聊消息发送
    int GroupJoin();//加入群
    int GroupInfoChange();//群信息变更

    int HandlePkg(CMsgBase* pMsg);

    virtual int Read();
    virtual int Write(CMsgBase* pMsg, CLIENT_INFO_T* client);

protected:
    virtual int Parse(uint8* pBuf, int32 &dwSize, CMsgBase** ppOutMsg);
    virtual int Pack(uint8* pBuf, int32 &dwSize, CMsgBase* pInMsg);

    int SendPkg(CLIENT_INFO_T* client);
    int RecvPkg();

    BUFFER_t    m_stSendBuffer, m_stRecvBuffer;//发送数据缓存，接受数据缓存
};

#endif /* _MSGSYSTEM_TESTCASE_H_ */