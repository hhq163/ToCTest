#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <time.h>
#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <string>
#include <cstring>
#include <list>
#include <vector>
#include <map>
#include <stdexcept>
#include <getopt.h>

#include <fstream>
#include <iostream>

#include "Common.pb.h"

using namespace std;
using namespace yunquan;



typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

typedef void (*FunCallback)(void* pParam, uint16 wFlag);

#define ntohll(x)   __bswap_64 (x)
#define htonll(x)   __bswap_64 (x)



//系统配置文件
#define SERVER_CONFIG_FILE "./server.cfg"

//error code
#define ERR_SUCCESS          0
#define ERR_FAILED          -1
#define ERR_NO_MORE_DATA    -2
#define ERR_NO_MORE_SPACE   -3
#define ERR_PROTOCOL        -4

//return code
#define RET_SUCCESS             0x0000
#define RET_ERROR               0x0001
#define RET_REDIRECT            0x0002
#define RET_NOTOUTH             0x0003
#define RET_DATAERROR           0x0004
#define RET_NOTINROOM           0x0005

#define RET_FAILED              0x1001
#define RET_VERSION_ERROR       0x1002
#define RET_USR_FORCE_DOWN      0x1030
#define RET_UNKNOWN_ERROR       0x1FFF


#define MOD_PUSH_SVR_ID          8700           //pushsvr module id
#define MAX_BUFFER_SIZE         1024*128        //128K


#define MAX_SOCKET_NUM          10000
#define MAX_CHECK_TIMEOUT       (3*60)          //3min
#define MAX_MODULE_TIMEOUT      120*100


#define MAX_TIME_OUT            5
#define MAX_HEARTBEAT           30      //30s
#define MAX_ONLINE_NUMS         10000
#define MAX_PACK_NUMS           50000

#define MAX_CONNMODULE_LIST_SIZE    50  //connect模块数量


#define MAX_MSG_LEN             1024
#define VISTORSYNC_BASE_TIME    5


//protocol version
/* for version <= 2.0 */
#define PROTOCOL_VERSION_0x1001 0x1001  //无加密
#define PROTOCOL_VERSION_0x2001 0x2001  //base64

#define PROTOCOL_HEAD_LEN       16

//compiled config
#define CFG_OBJECT_POOL
//#define CFG_SYNC_VC


#define MAX_SEND_MSG_INTERVAL   2
#define MAX_USERINFOINFO_LIST_SIZE  50


#define  CMD_INNER_FLAGE        (0x1 << 15)


const uint16 CMD_SYS_CLOSE_ALL_USER = 0x3101; //  关闭所有用户连接

const uint16 CMD_UNKNOW = 0x0FFF; //未知命令字

#define NO_ENCRYPT      0x0000  //无加密
#define ENCRYPT_BASE64  0x0001  //BASE64加密


#define SERVER_IP     "192.168.1.55"
#define SERVER_PORT     8200

#define CLIENT_IP      "127.0.0.1"
#define CLIENT_PORT     6500
#define USER_ID         10086
#define GROUP_ID        68

enum IO_TYPE
{
    IO_UDP_AUDIO_RTP = 0,
    IO_UDP_AUDIO_RTCP,
    IO_UDP_VIDEO_RTP,
    IO_UDP_VIDEO_RTCP,
    IO_TCP,
    IO_HTTP
};

enum IO_STATE
{
    IO_IDLE     = 0x00,
    IO_BUSY     = 0x01,
    IO_READ     = 0x02,
    IO_READING  = 0x04,
    IO_WRITE    = 0x08,
    IO_WRITING  = 0x10,
    IO_FINIT    = 0x80  //浮点检查初始化
};

enum IO_RESULT
{
    IO_SUCCESS = 0,
    IO_FAILED,
    IO_EAGAIN,
    IO_CLOSE,
    IO_TIMEOUT,
    IO_ERROR
};

enum TIMER_TYPE
{
    TIMER_CHECK_TIMEOUT = 1,
    TIMER_SVR_RECONNECT,
    TIMER_HEARTBEAT,
    TIMER_VISITOR_CALC
};

enum SERVER_TYPE
{
    ST_CONNECT_SVR  = 0x01,
    ST_LOGIC_SVR    = 0x02,
    ST_SYNC_SVR     = 0x03,
    ST_PUSH_SVR     = 0x04,
    ST_P2P_SVR      = 0x04,
    ST_P2P_MGR_SVR  = 0x05,
    ST_GROUP_SVR    = 0x06,
    ST_GROUP_MGR_SVR= 0x07,
    ST_WEB_SVR      = 0x08,
    ST_WEB_CLT      = 0x09,
    ST_BUSI_SVR     = 0x0a,
    ST_STATISTIC    = 0X0b
};

enum MODULE_TYPE
{
    MT_CLIENT = 0x01,
    MT_SERVER = 0x02
};
/**
 * 消息类型，删除消息时会用到
 */
enum MSG_TYPE
{
    MT_NORMAL       = 0x01,
    MT_GROUP_MSG    = 0x02, //群聊消息
    MT_PERSONAL_MSG = 0X03  //单聊消息
};

enum WEBSVR_TYPE
{
    WEB_TYPE    = 0x01,
    DB_TYPE     = 0x02
};



#define CHECK_IF_NULL(p)                                                        \
do                                                                              \
{                                                                               \
    if ( NULL == p )                                                            \
    {                                                                           \
        Logger.Log(ERROR, "this is a bug process must be exit....");            \
        sleep(1);                                                               \
        exit(0);                                                                \
    }                                                                           \
}while(0);

#endif
