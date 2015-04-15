/*
 * SvrFrame.h
 *
 *  Created on: 2015年4月15日
 *      Author: hhq163
 */

#ifndef SRC_MSGSYSTEM_SVRFRAME_H_
#define SRC_MSGSYSTEM_SVRFRAME_H_

/*
 *
 */
class SvrFrame {
public:
    SvrFrame();
    virtual ~SvrFrame();
public:
    int ClientInit(CLIENT_INFO_T* client);
    int ConnectTo(int* sockfd, CLIENT_INFO_T* client);

};

#endif /* SRC_MSGSYSTEM_SVRFRAME_H_ */
