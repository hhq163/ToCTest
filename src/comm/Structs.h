/**
 * 会用到的一些结构体
 */

#ifndef _STRUCT_H
#define _STRUCT_H

#include "Common.h"


#pragma pack(1) //指明下面结构体按照1字节方式进行对齐，无空字节

struct BUFFER_t
{
    uint32  iSize;
    uint32  iTotal;
    uint8   cBuffer[MAX_BUFFER_SIZE];
};

struct CLIENT_INFO_T
{
    pthread_t recvmsg_task_handle;
    pthread_t heartbeat_task_handle;
    int sockfd;
    int user_port;
    int user_id;
    int circle_id;
    bool islogin;
};

typedef struct
{
    uint32  dwMid;  //模块ID
    uint16  wType;
    uint32  dwIp;
    uint16  wPort;
    uint32  dwOnline;
    uint64  total;  //物理内存总数
    uint64  used;   //用了多少内存
    uint64  free;   //可用内存

}MODULE_INFO_t;

typedef struct SERVERINFO
{
    uint32  ip;
    uint32  port;
    uint16  type;       // 1表示connector模块 2表示groupserver模块
    uint32  count;      //Connector模块人数
    uint32  maxcount;   //支持最大人数

    uint32  count1;     //groupserv模块当前圈子数
    uint16  flag;       // 1表示空闲 2表示正常 3接近上限 4超负荷

    uint64  total;      //物理内存总数
    uint64  used;       //用了多少内存
    uint64  free;       //可用内存

    SERVERINFO()
    {
        clean();
    }

    void clean()
    {
        ip = 0;
        port = 0;
        type = 0;
        count = 0;
        maxcount = 0;

        count1 = 0;
        flag = 0;

        total = 0;
        used = 0;
        free = 0;

    }

    SERVERINFO &operator =( const SERVERINFO &info )
     {
        ip          = info.ip;
        port        = info.port;
        count       = info.count;
        flag        = info.flag;
        type        = info.type;
        maxcount    = info.maxcount;

        count1      = info.count1;
        total       = info.total;
        used        = info.used;
        free        = info.free;

        return *this;
     }

}SERVERINFO;

typedef struct PACKED_MEM       //定义一个mem occupy的结构体
{
    char name[20];      //定义一个char类型的数组名name有20个元素
    unsigned long total;
    char name2[20];
    unsigned long free;
}MEM_OCCUPY;

typedef struct PACKED_CPU       //定义一个cpu occupy的结构体
{
    char name[20];  //定义一个char类型的数组名name有20个元素
    uint32 user;    //定义一个无符号的int类型的user
    uint32 nice;    //定义一个无符号的int类型的nice
    uint32 system;  //定义一个无符号的int类型的system
    uint32 idle;    //定义一个无符号的int类型的idle

}CPU_OCCUPY;

/**
 * 用户信息结构体
 */
typedef struct _userinfo_
{
    uint32 uid;
    uint16 clientType;
    uint16 version;
    uint16 connectorsvrId;  //接入层ID

    _userinfo_()
    {
        clean();
    }
    void clean()
    {
        uid          = 0;
        clientType   = 0;
        version      = PROTOCOL_VERSION_0x1001;
        connectorsvrId = 0;
    }

     _userinfo_ &operator =( const _userinfo_ &userinfo )
     {
        uid             = userinfo.uid;
        clientType      = userinfo.clientType;
        version         = userinfo.version;
        connectorsvrId  = userinfo.connectorsvrId;
        return *this;
     }

}t_USERINFO;

typedef struct USER_MAPINFO
{
    uint64  userkey;
    uint32  dwUid;
    uint16  clientype;
    uint16  offflg;
    uint16  flg;

    t_USERINFO  userinfo;
    time_t t;
    USER_MAPINFO()
    {
        clean();
    }
    void clean()
    {
        userinfo.clean();
        userkey     = 0;
        dwUid       = 0;
        clientype   = 0;
        flg         = 0;
        t           = 0;
        offflg      = 0;
    }
}USER_MAPINFO;



#pragma pack()

class CMsgBase;
typedef struct
{
    CMsgBase* pMsg;
    time_t t;
}MSGCACHE_INFO_T;

typedef map<uint64, t_USERINFO> MAPVUSER; //uid

#endif
