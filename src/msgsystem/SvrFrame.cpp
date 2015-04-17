/*
 * SvrFrame.cpp
 *
 *  Created on: 2015年4月15日
 *      Author: hhq163
 */

#include "Common.h"
#include "Log.h"
#include "Config.h"
#include "SvrFrame.h"

SvrFrame::SvrFrame() {
    // TODO Auto-generated constructor stub

}

SvrFrame::~SvrFrame() {
    // TODO Auto-generated destructor stub
}
/**
 * 客户端初始化
 */
int SvrFrame::ClientInit(CLIENT_INFO_T* client){
    memset(client, 0x00, sizeof(CLIENT_INFO_T));

    client->sockfd = 0;
    client->user_port = CLIENT_PORT;
    client->user_id = USER_ID;
    client->circle_id = GROUP_ID;
    client->islogin = false;

    if (!Logger.Init(g_oConfig.m_dwID, 0, 0))
    {
        printf("log init failed!!!\r\n");
        return -1;
    }
    /* 设置打印级别 */
    Logger.SetLogLevel(g_oConfig.m_wLogLevel, true);


    return ERR_SUCCESS;
}

/**
 * 建立长连接
 */
int SvrFrame::ConnectTo(int* sockfd, CLIENT_INFO_T* client){
    int ret = 0;
    printf("ConnectTo (in)\n");

    struct sockaddr_in my_addr;
    struct sockaddr_in dest_addr; /* will hold the destination addr */

    //检查socket是否连通
    if((*sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Socket Error, %d\n", errno);
        return ERR_FAILED;
    }

    //绑定socket
    my_addr.sin_family = AF_INET;                       /* host byte order */
    my_addr.sin_port = htons(client->user_port); /* see man htons for more information */
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);            /* get our address */
    bzero(&(my_addr.sin_zero), 8);                      /* zero out the rest of the space */

    while(1)
    {
        ret = bind(*sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
        if(ret == -1)
        {
            my_addr.sin_port = htons(++(client->user_port));;
            printf("trying to bind... \n");
        }else{
            printf("binded \n");
            break;
        }
    }

    //远程连接
    dest_addr.sin_family = AF_INET;                 /* host byte order */
    dest_addr.sin_port = htons(SERVER_PORT);          /* short, network byte order */
    dest_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    bzero(&(dest_addr.sin_zero), 8);                /* zero the rest of the struct */

    if(connect(*sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
    {
        printf("Connection Error, %d\n", errno);
        //close(sockfd);
        return ERR_FAILED;
    }

    printf("ConnectTo (out)\n");
    return ERR_SUCCESS;
}
