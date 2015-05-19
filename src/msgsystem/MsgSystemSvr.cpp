#include "Common.h"
#include "Log.h"
#include "SvrFrame.h"
#include "TestCase.h"

using namespace std;

TestCase testCase;
static CLIENT_INFO_T client_info_t[1];

/**
 * 线程回调函数
 */
void* RecvmsgTask(void *param)
{
    testCase.Read(client_info_t);
    return NULL;
}

void* HeartbeatTask(void *param)
{
    testCase.HeartBeat(client_info_t);
    return NULL;
}

/**
 * 测试主程序
 */
int main(int argc, char **argv)
{
    int caseId = 0;
    int ret;
    memset(client_info_t, 0x00, sizeof(CLIENT_INFO_T));

    SvrFrame svrFrame;

    //客户端初如化
    svrFrame.ClientInit(client_info_t);
    //建立长连接
    svrFrame.ConnectTo(&client_info_t->sockfd, client_info_t);

    /* recv message thread */
    ret = pthread_create(&client_info_t->recvmsg_task_handle, NULL, RecvmsgTask, (void *)&client_info_t->sockfd);
    if (ret != 0)
    {
         printf("SendMsgTask thread create failure.\n");
    }


    /* heartbeat task thread */
    ret = pthread_create(&client_info_t->heartbeat_task_handle, NULL, HeartbeatTask, (void *)&client_info_t->sockfd);
    if (ret != 0)
    {
         printf("heartbeat  thread create failure.\n");
    }

    //用户登录
    testCase.UserLogin(client_info_t);

    cout << "Enter TestCase ID number: \n" <<
            "(1) GroupMsgSend test; \n"<<
            "(2) GroupJoin test; \n"<<
            "(3) GroupInfoChange test; \n"<<
            "(4) PersonalMsgSend test; \n"<<
            "(5) MsgSync test; \n"<<
            "(6) Exit test System; \n"<<
            endl;
    cin >> caseId;


    switch(caseId){
    case 1:
        testCase.GroupMsgSend(client_info_t);
        break;
    case 2:
        testCase.GroupJoin();
        break;
    case 3:
        testCase.GroupInfoChange();
        break;
    case 4:
        testCase.PersonalMsgSend(client_info_t);
        break;
    case 5:
        testCase.MsgSync(client_info_t);
        break;
    case 6:
        break;
    default:
        cout << "Your enter is error ,please " << endl;
        break;
    }


    return ERR_SUCCESS;
}


