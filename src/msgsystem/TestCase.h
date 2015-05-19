/*
 * TestCase.h
 *
 *  Created on: 2015年4月15日
 *      Author: hhq163
 */

#ifndef _MSGSYSTEM_TESTCASE_H_
#define _MSGSYSTEM_TESTCASE_H_

class ModuleMgr;
/*
 * 测试用例
 */
class TestCase {
public:
    TestCase();
    virtual ~TestCase();

    int UserLogin(CLIENT_INFO_T* userClient);
    int GroupMsgSend(CLIENT_INFO_T* userClient);//群聊消息发送
    int GroupJoin();//加入群
    int GroupInfoChange();//群信息变更
    int PersonalMsgSend(CLIENT_INFO_T* userClient);//单聊消息发送
    int MsgSync(CLIENT_INFO_T* userClient);//消息同步
    int DoSyncMsg(CLIENT_INFO_T* userClient);//发送同步请求

    int HandlePkg(CMsgBase* pMsg);

    virtual int Read(CLIENT_INFO_T* userClient);
    virtual int Write(CMsgBase* pMsg, CLIENT_INFO_T* userClient);
    virtual int HeartBeat(CLIENT_INFO_T* userClient);

protected:
    virtual int Parse(uint8* pBuf, int32 &dwSize, CMsgBase** ppOutMsg);
    virtual int Pack(uint8* pBuf, int32 &dwSize, CMsgBase* pInMsg);

    int SendPkg(CLIENT_INFO_T* userClient);
    int RecvPkg(CLIENT_INFO_T* userClient);

    BUFFER_t    m_stSendBuffer, m_stRecvBuffer;//发送数据缓存，接受数据缓存

    ModuleMgr*             m_pMgr;
};

#endif /* _MSGSYSTEM_TESTCASE_H_ */
