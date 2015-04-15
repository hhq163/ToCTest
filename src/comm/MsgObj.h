#ifndef _MSG_OBJECT_H_
#define _MSG_OBJECT_H_

#include "Common.h"
/**
 * 消息体基类
 */
struct MsgObjBase
{

};
/**
 * 系统消息
 */
struct MsgSystem : MsgObjBase
{
    uint32 type;
    string msg;
    MsgSystem(){
        type = 0;
    };
};

/**
 * 文本类型
 */
struct MsgText : MsgObjBase
{
    uint32 type;
    string msg;
    MsgText(){
        type = 0;
    };
};
/**
 * 图片类型
 */
struct MsgImage : MsgObjBase
{
    uint32 w;
    uint32 h;
    string url;
    string thumbnailUrl;
    MsgImage()
    {
        w = 0;
        h = 0;
    };
};
/**
 * 语音类型
 */
struct MsgVoice : MsgObjBase
{
    uint32 len;
    string url;
    MsgVoice(){
        len = 0;
    };
};
/**
 * 视频类型
 */
struct MsgVedio : MsgObjBase
{
    uint32 len;
    string url;
    MsgVedio()
    {
        len = 0;
    };
};
/**
 * 图文链接类型
 */
struct MsgLink : MsgObjBase
{
    string title;
    string msg;
    string url;
    string imageUrl;
};
/**
 * 名片类型
 */
struct MsgCard : MsgObjBase
{
    uint32 uid;
    string name;
    string portrait;
    string phone;
    string company;
    string title;
    MsgCard()
    {
        uid = 0;
    };
};

#endif
