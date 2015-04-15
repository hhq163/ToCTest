/*
 * TestCase.cpp
 * 测试用例类
 *  Created on: 2015年4月15日
 *      Author: hhq163
 */

#include "Common.h"
#include "Log.h"
#include "ChatMsg.pb.h"
#include "TestCase.h"

TestCase::TestCase() {
    // TODO Auto-generated constructor stub
    UserLogin();
}

TestCase::~TestCase() {
    // TODO Auto-generated destructor stub
}
/**
 * 用户登录
 */
int TestCase::UserLogin(){
    cout << "YTestCase::UserLogin (in) \n" << endl;


    cout << "YTestCase::UserLogin (out) \n" << endl;
    return ERR_SUCCESS;
};
/**
 * 群聊消息发送
 */
int TestCase::GroupMsgSend(CLIENT_INFO_T* client){
    cout << "YTestCase::GroupMsgSend (in) \n" << endl;

    int8 msg_send[1024] = {'\0'};
    int sendcase = 0;
    int ret = 0;

    struct timeval tv;
    gettimeofday(&tv, NULL) ;

    while(1 == sendcase){
        cout << "Please input the msg your want to send: \n" << endl;
        cin >> msg_send;
        if(strlen(msg_send) != 0){
            MsgText* msgText = new MsgText();
            msgText->type = 1;
            msgText->msg = msg_send;
            CChatMsgSend* pCChatMsgSend = (CChatMsgRecv*)CMsgBase::NewMsg(CMD_MSG_GROUP_SEND);
            pCChatMsgSend->m_dwFromUid = GROUP_ID;
            pCChatMsgSend->m_dwSeqId = 16;
            pCChatMsgSend->m_dwObjType = MOT_TEXT;
            pCChatMsgSend->m_sendtime = time(0);
            pCChatMsgSend->m_MsgObjBase = msgText;
            pCChatMsgSend->m_msgId  = (tv.tv_sec * 1000000 + tv.tv_usec);

            Write(pCChatMsgSend, client);
            if(ret < 0)
            {
                printf("message send failure. ret=%d\n", ret);
                return ERR_FAILED;
            }
        }else{//如果输入是空，跳出程序
            sendcase = 1;
        }

    }



    cout << "YTestCase::GroupMsgSend (out) \n" << endl;
    return ERR_SUCCESS;
};

/**
 * 加入群
 */
int TestCase::GroupJoin(){
    cout << "YTestCase::GroupJoin (in) \n" << endl;

    cout << "YTestCase::GroupJoin (out) \n" << endl;
    return ERR_SUCCESS;
};

/**
 * 群信息变更
 */
int TestCase::GroupInfoChange(){
    cout << "YTestCase::GroupInfoChange (in) \n" << endl;

    cout << "YTestCase::GroupInfoChange (out) \n" << endl;
    return ERR_SUCCESS;
};


/**
 * 消息读取
 */
int TestCase::Read()
{
    int iRet = IO_SUCCESS;
    do
    {
        iRet = RecvPkg();

        if (m_stRecvBuffer.iSize > 0)
        {
            int dwRead = 0;
            int dwSize = m_stRecvBuffer.iSize;
            uint8* p   = m_stRecvBuffer.cBuffer;
            do
            {
                CMsgBase* pMsg = NULL;
                int iErr = Parse(p, dwSize, &pMsg);
                if (ERR_SUCCESS == iErr)
                {
                    pMsg->m_pRoute = this;
                    if (ERR_SUCCESS == HandlePkg(pMsg))
                    {
                        CMsgBase::DelMsg(pMsg);
                    }

                    if (dwRead + dwSize == (int)m_stRecvBuffer.iSize)
                    {
                        m_stRecvBuffer.iSize = 0;
                        break;
                    }
                }
                else if (ERR_NO_MORE_DATA == iErr)
                {
                    if (p != m_stRecvBuffer.cBuffer)
                    {
                        int dwLen = m_stRecvBuffer.iSize - dwRead;
                        memmove(m_stRecvBuffer.cBuffer, p, dwLen);
                        m_stRecvBuffer.iSize = dwLen;
                    }
                    else
                    {
                        if (m_stRecvBuffer.iSize >= MAX_BUFFER_SIZE)
                        {
                            Logger.Log(NOTIC, "the msg size is more than the max buffer");
                            m_stRecvBuffer.iSize = 0;
                        }
                    }
                    break;
                }
                else
                {
                    iRet = IO_CLOSE;
                    Logger.Log(NOTIC, "revc err protocol close");
                    break;
                }

                p      += dwSize;
                dwRead += dwSize;
                dwSize  = m_stRecvBuffer.iSize - dwRead;

            } while (dwRead < (int)m_stRecvBuffer.iSize);
        }

        if (IO_CLOSE == iRet)
        {
//            Close(IO_CLOSE);
        }

    } while (IO_SUCCESS == iRet);

    return ERR_SUCCESS;
}


/**
 * 消息发送
 */
int TestCase::Write(CMsgBase* pMsg, CLIENT_INFO_T* client)
{
    int iRet = IO_SUCCESS;
    do
    {
        if (0 == m_stSendBuffer.iSize && 0 == m_stSendBuffer.iTotal)
        {

            int dwSize = MAX_BUFFER_SIZE;
            int iErr = Pack(m_stSendBuffer.cBuffer, dwSize, pMsg);

            if (CMD_SYS_HEART_BEAT != pMsg->m_wCmd && CMD_SYS_HEART_BEAT_ACK != pMsg->m_wCmd)
            {
                Logger.Log(NOTIC, "<<<<<<  write cmd:[0x%04x] [0x%04x] , to user:%lld, err:%d",\
                    (pMsg->m_wCmd), (pMsg->m_wCmd) & ~CMD_INNER_FLAGE, pMsg->m_dwId, iErr);
            }


            if (CMD_SYS_HEART_BEAT != pMsg->m_wCmd)
            {
                CMsgBase::DelMsg(pMsg);
            }

            if (ERR_SUCCESS != iErr)
            {
                continue;
            }

            m_stSendBuffer.iTotal = dwSize;
        }

        iRet = SendPkg(client);

    } while (IO_SUCCESS == iRet);

    return ERR_SUCCESS;
}

/**
 * 数据发送
 */
int TestCase::SendPkg(CLIENT_INFO_T* client)
{
    int iErr = IO_FAILED;

    while (client->sockfd >= 0  && m_stSendBuffer.iSize < m_stSendBuffer.iTotal)
    {
        Logger.Log(DEBUG, "buffer total:%d size:%d", m_stSendBuffer.iTotal, m_stSendBuffer.iSize);
        int iRet = send(client->sockfd, m_stSendBuffer.cBuffer + m_stSendBuffer.iSize, m_stSendBuffer.iTotal - m_stSendBuffer.iSize, 0);
        if (iRet < 0)
        {
            if (EAGAIN == errno)
            {
                iErr = IO_EAGAIN;
                break;
            }

            Logger.Log(DEBUG, "socket:%d send error:%s", client->sockfd, strerror(errno));
            iErr = IO_CLOSE;
            break;
        }
        else if(iRet == 0)
        {
        }
        else
        {
            iErr = IO_SUCCESS;
            m_stSendBuffer.iSize += iRet;
            if (m_stSendBuffer.iSize == m_stSendBuffer.iTotal)
            {
                m_stSendBuffer.iSize  = 0;
                m_stSendBuffer.iTotal = 0;
                memset(m_stSendBuffer.cBuffer, 0x00, sizeof(m_stSendBuffer.cBuffer));
                break;
            }
        }
    }

    return iErr ;
}

/**
 * 协议包解析，解析CModule收到的数据包
 * @param   pBuf        数据源
 * @param   dwSize  数据源长度
 * @param   ppOutMsg (out)CMsgBase对象指针的指针，包体为IM协议包
 * @return  ERR_SUCCESS 成功
            ERR_FAILED 失败
            ERR_NO_MORE_DATA 包体数据缺失
 */
int TestCase::Parse(uint8* pBuf, int32 &dwSize, CMsgBase** ppOutMsg)
{
    return CMsgBase::NewMsgFromBuf(pBuf, dwSize, ppOutMsg);
}

/**
 * 消息协议包封装, 将消息协议包封装到http协议包中
 * @param   pBuf        封装后的数据
 * @param   dwSize  封装后的数据长度
 * @param   pInMsg  CMsgBase对象指针，IM协议包
 * @return  ERR_SUCCESS 成功
            ERR_FAILED 失败
 */
int TestCase::Pack(uint8* pBuf, int32 &dwSize, CMsgBase* pInMsg)
{
    return CMsgBase::GetBufFromMsg(pBuf, dwSize, pInMsg);
}

/**
 * 消息处理
 */
int TestCase::HandlePkg(CMsgBase* pMsg)
{
    switch(pMsg->m_wCmd)
    {
        case CMD_USER_LOGIN:
        {
            Logger.Log(INFO, " The CMD_USER_LOGIN CMD request come back!");
            break;
        }
        case CMD_MSG_GROUP_SEND:
        {
            Logger.Log(INFO, "The CMD_MSG_GROUP_SEND CMD request come back!");
            break;
        }
        default:
            break;
    }
    return ERR_SUCCESS;
}
