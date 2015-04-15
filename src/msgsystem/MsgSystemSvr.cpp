#include "Common.h"
#include "Log.h"
#include "TestCase.h"
#include "gtest.h"

using namespace std;

/*
TEST(TestCase, GroupMsgSend){
    TestCase tc;
    EXPECT_EQ(1, tc.GroupMsgSend("this is my first message!!!"));
    EXPECT_EQ(1, tc.GroupMsgSend("second"));
    EXPECT_EQ(1, tc.GroupMsgSend("third"));
}*/

TestCase testCase;

/**
 * 测试主程序
 */
int main(int argc, char **argv)
{
    int caseId = 0;

    int ret;

    CLIENT_INFO_T* client_info_t;

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

#if 0
    /* heartbeat task thread */
    ret = pthread_create(&client_info_t->heartbeat_task_handle, NULL, heartbeat_task, (void *)&client_info_t->sockfd);
    if (ret != 0)
    {
         printf("heartbeat  thread create failure.\n");
    }
#endif
    //暂不做用户登录

    while(4 != caseId){
        cout << "Enter TestCase ID number: \n" <<
                "(1) GroupMsgSend test; \n"<<
                "(2) GroupJoin test; \n"<<
                "(3) GroupInfoChange test; \n"<<
                "(4) Exit test System; \n"<<
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
            break;
        default:
            cout << "Your enter is error ,please " << endl;
            break;
        }

    }

    return ERR_SUCCESS;
}
/**
 * 线程回调函数
 */
void* RecvmsgTask(void *param)
{
    testCase.Read();
    return NULL;
}

