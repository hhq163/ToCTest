#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "Common.h"
#include "Struct.h"
#include "base64.h"

#include "Common.pb.h"
using namespace yunquan;

#include "CMsgBase.h"
#include "CMsgBaseAck.h"

#include "CRoomMsg.h"


#include "CMsgUserLogin.h"
#include "CMsgUserLoginAck.h"

#include "CMsgModuleLogin.h"
#include "CMsgModuleLoginAck.h"

#include "CMsgHeartbeat.h"
#include "CMsgHeartbeatAck.h"


#include "CChatMsgSend.h"
#include "CChatMsgRecv.h"

//群聊相关
#include "CMsgNotify.h"
#include "CCSGroupUserListGetAck.h"
#include "CCSGroupUserListGet.h"


#endif
