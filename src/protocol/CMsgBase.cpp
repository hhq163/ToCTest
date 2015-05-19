//#include "Log.h"
//#include "Common.h"
//#include "Struct.h"
//#include "base64.h"
//#include "ProtJsonGetValue.h"

#include "Prot.h"
#include "Log.h"
#include "CMsgBase.h"

CMsgBase::CMsgBase():
m_wVer(PROTOCOL_VERSION_0x1001),m_dwLen(PROTOCOL_HEAD_LEN),m_dwSeqId(0),m_wCmd(CMD_UNKNOW),
m_dwId(0),m_dwSessionId(0),m_pBuf(NULL),m_Buflen(0),
m_wType(MT_NORMAL),m_pRoute(NULL)
{
    m_wVer     = PROTOCOL_VERSION_0x1001;
    m_dwLen    = PROTOCOL_HEAD_LEN;
    m_dwSeqId  = 0;
    m_wCmd     = CMD_UNKNOW;
    m_dwId     = 0;
    m_pRoute   = NULL;
    m_dwSessionId = 0;
    m_pBuf     = NULL;
}

CMsgBase::~CMsgBase()
{
    if( NULL != m_pBuf )
    {
        delete[] m_pBuf;
        m_pBuf = NULL;
    }
}

CMsgBase* CMsgBase::Clone()
{
    return NULL;
}

int CMsgBase::NewMsgFromBuf(uint8* pBuf, int32 &dwSize, CMsgBase** ppOutMsg)
{
    if (NULL == pBuf || dwSize <= 0)
    {
        Logger.Log(ERROR, "new msg from buf failed, bad parameter! dwSize[%d]", dwSize);
        return ERR_FAILED;
    }

    uint8* p = pBuf;

    if (dwSize < (uint32)PROTOCOL_HEAD_LEN)
    {
        return ERR_NO_MORE_DATA;
    }

    uint32 dwLen    = ntohl(*((uint32*)p));
    p+=4;
    uint16 wVer     = ntohs(*((uint16*)p));
    p+=2;
    uint16 wCmd     = ntohs(*((uint16*)p));
    p+=2;
    uint32 dwSeqId   = ntohl(*((uint32*)p));
    p+=4;
    uint32 dwId = ntohl(*((uint32*)p));
    p += 4;
    Logger.Log(INFO, ">>>>>> m_dwLen=%u, m_wVer=0x%04x, m_wCmd=0x%04x dwSeqId=%u dwId=%u", dwLen, wVer, wCmd, dwSeqId, dwId);
    switch (wVer)
    {
    case PROTOCOL_VERSION_0x1001:
    case PROTOCOL_VERSION_0x2001:
        break;
    default:
        Logger.Log(ERROR, "parse data, the ver:0x%04x is error! cmd:0x%04x", wVer, wCmd);
        return ERR_PROTOCOL;
        break;
    }


    if (dwSize < (int32)dwLen)
    {
        Logger.Log(ERROR, "parse data, the buffer size:%d is less than the msg size:%d, cmd:0x%04x dwDesUid[%u]",
            dwSize, dwLen, wCmd, dwId);
        return ERR_NO_MORE_DATA;
    }

    //Logger.Log(ERROR, "parse data,ver:0x%04x, cmd:0x%04x, len:%d, size:%d dwId[%d]",wVer, wCmd, dwLen, dwSize,dwId);
    *ppOutMsg = CMsgBase::NewMsg(wCmd);
    if (NULL == *ppOutMsg)
    {
        Logger.Log(ERROR, "NewMsg failed, cmd:0x%04x", wCmd);
        return ERR_FAILED;
    }


    int iErr = (*ppOutMsg)->Parse(pBuf, dwSize);
    if (ERR_SUCCESS != iErr)
    {
        Logger.Log(ERROR, "Msg parse failed, cmd:0x%04x", wCmd);
        CMsgBase::DelMsg(*ppOutMsg);
        *ppOutMsg = NULL;
    }

    return iErr;
}

int CMsgBase::GetBufFromMsg(uint8* pBuf, int32 &dwSize, CMsgBase* pInMsg)
{
    if (NULL == pBuf || NULL == pInMsg)
    {
        Logger.Log(ERROR, "get buf from msg failed, bad parameter!");
        return ERR_FAILED;
    }


    switch (pInMsg->m_wVer)
    {
    case PROTOCOL_VERSION_0x1001:
    case PROTOCOL_VERSION_0x2001:
        break;
    default:
        Logger.Log(ERROR, "GetBufFromMsg, the ver:0x%04x is error! cmd:[0x%04x] m_llDesUid:%u",
            pInMsg->m_wVer, pInMsg->m_wCmd, pInMsg->m_dwId);
        return ERR_FAILED;
        break;
    }

    if (dwSize < (int32)pInMsg->m_dwLen)
    {
        Logger.Log(ERROR, "pack data, the buffer size:%d is less than the msg size:%d, cmd:[0x%04x]  m_llDesUid:%u ",\
            dwSize, pInMsg->m_dwLen, pInMsg->m_wCmd, pInMsg->m_dwId);

        return ERR_NO_MORE_SPACE;
    }

    return pInMsg->Pack(pBuf, dwSize);
}

/**
 * 创建消息对象,根据wCmd创建不同类型的消息对象，并返回对象指针
 * @param   wCmd        命令字
 * @return  对象指针
 */

CMsgBase* CMsgBase::NewMsg(uint16 wCmd)
{
    //return gNewMsg(wCmd);
    CMsgBase * pMsg = NULL;
    //wCmd  &=  (~CMD_INNER_FLAGE);
    uint16 wBaseCmd = wCmd & (~CMD_INNER_FLAGE);
    switch (wBaseCmd)
    {

    //内部消息
    case CMD_SYS_MODULE_LOGIN:
        pMsg = new CMsgModuleLogin();
        break;

    case CMD_SYS_MODULE_LOGIN_ACK:
        pMsg = new CMsgModuleLoginAck();
        break;

    case CMD_SYS_MODULE_LOGOUT:
        pMsg = new CMsgBase();
        break;

    case CMD_SYS_HEART_BEAT:
        pMsg = new CMsgBase();
        break;

    case CMD_SYS_HEART_BEAT_ACK:
        pMsg = new CMsgHeartbeatAck();
        break;

    case CMD_SYS_USER_CLOSE:
        pMsg = new CMsgBase();
        break;

    case CMD_SYS_USER_CLOSE_ALL:
        pMsg = new CMsgBase();
        break;

    //用户协议
    case CMD_USER_LOGIN:
        pMsg = new CMsgUserLogin();
        break;

    case CMD_USER_LOGIN_ACK:
        pMsg = new CMsgUserLoginAck();
        break;

    case CMD_USER_LOGOUT:
        pMsg = new CMsgUserLogout();
        break;

    case CMD_USER_HEARTBEAT:
        pMsg = new CMsgBase();
        break;

    case CMD_USER_FORCE_OFFLINE:
        pMsg = new CMsgForceOffline();
        break;

    case CMD_MSG_P2P_SEND:
        pMsg = new CChatMsgSend();
        break;

    case CMD_MSG_P2P_RECV:
        pMsg = new CChatMsgRecv();
        break;

    case CMD_MSG_GROUP_SEND:
        pMsg = new CChatMsgSend();
        break;

    case CMD_MSG_GROUP_RECV:
        pMsg = new CChatMsgRecv();
        break;

    case CMD_MSG_NOTIF:
        pMsg = new CMsgNotify();
        break;

    case CMD_MSG_NOTIF_ACK:
        pMsg = new CMsgNotifyAck();
        break;

    case CMD_MSG_SYNC:
        pMsg = new CMsgSync();
        break;

    case CMD_MSG_PUSH:
        pMsg = new CMsgPush();
        break;

    case CMD_USER_HEARTBEAT_ACK:
    case CMD_USER_LOGOUT_ACK:
    case CMD_MSG_P2P_SEND_ACK:
    case CMD_MSG_P2P_RECV_ACK:
    case CMD_MSG_GROUP_SEND_ACK:
    case CMD_MSG_GROUP_RECV_ACK:
    case CMD_MSG_SYNC_ACK:
    case CMD_MSG_PUSH_ACK:
    case CMD_GROUP_MEMBER_ADD_ACK:
    case CMD_ENTER_ACTIVITY_ROOM_ACK:
    case CMD_EXIT_ACTIVITY_ROOM_ACK:
        pMsg = new CMsgBaseAck();
        break;

     /* 群聊相关协议 */
    case CMD_CS_GROUP_USER_LIST_GET:
        pMsg = new CCSGroupUserListRequest();
        break;

    case CMD_CS_GROUP_USER_LIST_GET_ACK:
        pMsg = new CCSGroupUserListAck();
        break;

    case CMD_GROUP_MEMBER_ADD:
        pMsg = new CCSGroupUserAdd();
        break;

    /* 活动相关 */
    case CMD_ENTER_ACTIVITY_ROOM:
        pMsg = new CMsgActivityRoom();
        break;

    case CMD_EXIT_ACTIVITY_ROOM:
        pMsg = new CMsgActivityRoom();
        break;

    default:
        return NULL;
    }
    pMsg->m_wVer = PROTOCOL_VERSION_0x1001;
    pMsg->m_wCmd = wCmd;
    return pMsg;

}


void CMsgBase::DelMsg(CMsgBase* pMsg)
{
    if (NULL == pMsg)
    {
        return;
    }
#if 0
    if ( MT_GROUP_MSG == pMsg->m_wtype )
    {
        CRoomMsg* pRoomMsg = (CRoomMsg*)pMsg;
        CRoomMsg::DelRoomMsg(pRoomMsg);
    }
    else if (MT_PERSONAL_MSG == pMsg->m_wtype)
    {
        CMsgPersonalMsgRecv* pPersonalMsg = (CMsgPersonalMsgRecv*)pMsg;
        CMsgPersonalMsgRecv::DelPersonalMsg(pPersonalMsg);
    }
    else
    {
#endif
        delete pMsg;
        pMsg = NULL;
//    }

}


int CMsgBase::GetEncryptType()
{
    switch (m_wVer)
    {
    case PROTOCOL_VERSION_0x1001:
        return NO_ENCRYPT;
    case PROTOCOL_VERSION_0x2001:
        return ENCRYPT_BASE64;
    default:
        Logger.Log(ERROR, "Err cmd[0x%04x] m_wVer[0x%04x] set  NO_ENCRYPT", m_wCmd, m_wVer);
        return NO_ENCRYPT;
    }
    return NO_ENCRYPT;
}


int CMsgBase::Parse(uint8* pBuf, int32 &dwSize)
{
    uint8* p   = pBuf;
    m_dwLen    = ntohl(*((uint32*)p));
    p += 4;
    m_wVer     = ntohs(*((uint16*)p));
    p += 2;
    m_wCmd     = ntohs(*((uint16*)p));
    p += 2;
    m_dwSeqId  = ntohl(*((uint32*)p));
    p += 4;
    m_dwId = ntohl(*((uint32*)p));
    p += 4;

    dwSize = (int32)(p - pBuf );

    return ERR_SUCCESS;
}


int CMsgBase::Pack(uint8* pBuf, int32 &dwSize)
{
    Logger.Log(ERROR, "CMsgBase::Pack (in)  cmd[0x%04x]", m_wCmd);
    uint8* p      = pBuf;
    *((uint32*)p) = htonl(m_dwLen);
    p += 4;
    *((uint16*)p) = htons(m_wVer);
    p += 2;
    *((uint16*)p) = htons(m_wCmd);
    p += 2;
    *((uint32*)p) = htonl(m_dwSeqId);
    p += 4;
    *((uint32*)p) = htonl(m_dwId);
    p += 4;

    dwSize = (int32)(p - pBuf);
    Logger.Log(ERROR, "CMsgBase::Pack (out) cmd[0x%04x]", m_wCmd);
    return ERR_SUCCESS;
}


void CMsgBase::UpdateLen(uint8* pBuf, uint32 dwLen)
{
    *((uint32*)pBuf) = htonl(dwLen);
}


int CMsgBase::Encrypt(const char* src, uint32 srclen, char* des, uint32 deslen)
{
    if ( NULL == src || NULL == des )
    {
        Logger.Log(ERROR, "Err Encrypt dstuid[%u] cmd[0x%04x] src==NULL || des == NULL", m_dwId, m_wCmd);
        return -1;
    }
    if ( 0 == srclen || 0 == deslen )
    {
        Logger.Log(ERROR, "Err Encrypt dstuid[%u] cmd[0x%04x] srclen[%u] || deslen[%u]", m_dwId, m_wCmd, srclen ,deslen );
        return -1;
    }
    int nRet = 0;
    switch (GetEncryptType())
    {
    case ENCRYPT_BASE64:
    {
        if( 0 != ( nRet = base64_encode((unsigned char *)des, (int*)&deslen, (unsigned char *)src, (int)srclen)))
        {
            Logger.Log(ERROR, "base64_encode failed[%d] srclen[%d] deslen[%d]", nRet, srclen, deslen);
            return -1;
        }
        return deslen;
        break;
    }
    case NO_ENCRYPT:
    {
        memcpy(des, src, srclen);
        return srclen;
        break;
    }
    default:
    {
        Logger.Log(ERROR, "Err m_encrypt_type[%d]", GetEncryptType());
        return -1;
    }
    }

    return -1;
}


int CMsgBase::Decrypt(const char* src, uint32 srclen, char * & des, uint32 deslen)
{
    if ( NULL == src )
    {
        Logger.Log(ERROR, "Err Decrypt dstuid[%u] cmd[%p] src==NULL || des == NULL", m_dwId, m_wCmd);
        return -1;
    }

    if ( 0 == srclen || 0 == deslen )
    {
        Logger.Log(ERROR, "Err Decrypt dstuid[%u] cmd[%d] srclen[%u] || deslen[%u]", m_dwId, m_wCmd, srclen ,deslen );
        return -1;
    }

    int nRet = 0;
    switch (GetEncryptType())
    {
    case ENCRYPT_BASE64:
    {
        m_pBuf = new char[deslen + 1];
        m_pBuf[deslen] = '\0';
        des = m_pBuf;
        if ( 0 != ( nRet = base64_decode((unsigned char*)des, (int*)&deslen, (unsigned char*)src, (int)srclen)))
        {
            Logger.Log(ERROR, "base64_decode failed[%d] srclen[%d] deslen[%d]", nRet, srclen, deslen);
            return -1;
        }
        return deslen;
        break;
    }
    case NO_ENCRYPT:
    {
        des = (char*)src;
        return srclen;
        break;
    }
    default:
    {
        Logger.Log(ERROR, "Err m_encrypt_type[%d]", GetEncryptType());
        return -1;
    }
    }

    return -1;
}
