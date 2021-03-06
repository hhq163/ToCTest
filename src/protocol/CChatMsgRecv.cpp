/*
 * CChatMsgRecv.cpp
 */

#include "Common.h"
#include "Log.h"
#include "CChatMsgRecv.h"
#include "ChatMsg.pb.h"

 CChatMsgRecv::CChatMsgRecv()
 {
     m_dwFromUid = 0;
     m_sendtime = 0;
     m_dwObjType = 0;
     m_llSyncKey = 0;
 }
 
 CChatMsgRecv::~CChatMsgRecv()
 {
 
 }
 
 
 int CChatMsgRecv::Parse(uint8* pBuf, int32& dwSize)
 {
     uint8* p = pBuf;
     int32 dwUsedSize = dwSize;
     Logger.Log(ERROR, "CChatMsgRecv::Parse(in)");
 
     int iErr = CMsgBase::Parse(pBuf, dwUsedSize);
     if(ERR_SUCCESS != iErr)
     {
         return iErr;
     }
     p += dwUsedSize;
     m_pprotoBuf = (char *)p;
 
     m_Buflen = m_dwLen - dwUsedSize;
     if( m_Buflen > MAX_BUFFER_SIZE )
     {
         Logger.Log(ERROR, "parse msg bodylen[%d] > MAX_BUFFER_SIZE[%d] ", m_Buflen, MAX_BUFFER_SIZE);
         return ERR_FAILED;
     }
     if( m_dwLen > (uint32)dwSize )
     {
         return ERR_NO_MORE_DATA;
     }
 
     /*        check if need  Decrypt , ver??    */
     int nRet = 0;
     char* pdata = NULL;
     if( 0 > ( nRet = CMsgBase::Decrypt((const char*)p, m_dwLen - dwUsedSize, pdata, m_Buflen)))
     {
         Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Decrypt failed", m_wCmd, m_dwId);
         return ERR_FAILED;
     }
     CHECK_IF_NULL(pdata);
 
 //////////////////////////////////////////////////////////////////////////
     string strData(pdata, m_Buflen);
 
     ChatMsg *pChatMsg = new ChatMsg();
     pChatMsg->Clear();
 
     if (pChatMsg->ParseFromString(strData))
     {
         if(pChatMsg->has_fromuid())
         {
             m_dwFromUid = pChatMsg->fromuid();
         }
         if(pChatMsg->has_msgid())
         {
             m_msgId = pChatMsg->msgid();
         }
         if(pChatMsg->has_time())
         {
             m_sendtime = pChatMsg->time();
         }
         if(pChatMsg->has_synckey())
         {
             m_llSyncKey = pChatMsg->synckey();
         }

         if(pChatMsg->has_type())
         {
             m_dwObjType = pChatMsg->type();
         }
         if(pChatMsg->has_sessionid())
         {
             m_dwSessionId = pChatMsg->sessionid();
         }
         switch(pChatMsg->type())
         {
         case MOT_SYSTEM:
         {
             m_MsgObjBase = new MsgSystem();
             if(pChatMsg->has_objsystem())
             {
                 const MsgObjSystem &obj = pChatMsg->objsystem();
                 ((MsgSystem*)m_MsgObjBase)->type = obj.type();
                 ((MsgSystem*)m_MsgObjBase)->msg = obj.msg();
                 m_txt = obj.msg();
             }
             break;
         }
         case MOT_TEXT:
         {
             m_MsgObjBase = new MsgText();
             if(pChatMsg->has_objtext())
             {
                 const MsgObjText &obj = pChatMsg->objtext();
                 ((MsgText*)m_MsgObjBase)->type = obj.type();
                 ((MsgText*)m_MsgObjBase)->msg = obj.msg();
                 m_txt = obj.msg();
             }
             break;
         }
         case MOT_IMAGE:
         {
             m_MsgObjBase = new MsgImage();
             if(pChatMsg->has_objimage())
             {
                 const MsgObjImage &obj = pChatMsg->objimage();
                 ((MsgImage*)m_MsgObjBase)->w = obj.w();
                 ((MsgImage*)m_MsgObjBase)->h = obj.h();
                 ((MsgImage*)m_MsgObjBase)->url=obj.url();
                 ((MsgImage*)m_MsgObjBase)->thumbnailUrl = obj.thumbnailurl();
             }
             break;
         }
         default:
             m_MsgObjBase = NULL;
             break;
         }
 
         Logger.Log(INFO, "cmd:[0x%04x] m_dwDesUid:[%lld] m_dwSessionId:[%d]", \
             m_wCmd, m_dwId, m_dwSessionId);
 
         /*        Internal use            */
         if( m_wCmd & CMD_INNER_FLAGE )
         {
 
         }
 
     }
     else
     {
         Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Json parse  failed", m_wCmd, m_dwId);
         return ERR_FAILED;
     }
 //////////////////////////////////////////////////////////////////////////
     p += m_Buflen;
 
     dwSize = (int32)(p - pBuf );
     Logger.Log(ERROR, "CChatMsgRecv::Parse(out)");
     return ERR_SUCCESS;
 
 }
 
 
 int CChatMsgRecv::Pack(uint8* pBuf, int32& dwSize)
 {
     Logger.Log(ERROR, "CChatMsgRecv::Pack(in)");
     uint8* p = pBuf;
     int32 dwUsedSize = dwSize;
     int iErr = CMsgBase::Pack(p, dwUsedSize);
     if(ERR_SUCCESS != iErr)
     {
         return iErr;
     }
     p += dwUsedSize;
 
 ////////////////////////////////////////////////////////////////
     /*  ProtocolBuffer pack */
 
     ChatMsg *pChatMsg = new ChatMsg();
     pChatMsg->Clear();
 
     pChatMsg->set_fromuid(m_dwFromUid);
     pChatMsg->set_msgid(m_msgId);
     pChatMsg->set_time(m_sendtime);
     pChatMsg->set_synckey(m_llSyncKey);
     pChatMsg->set_type((E_MSG_OBJECT_TYPE)m_dwObjType);
     if(m_dwSessionId != 0)
     {
         pChatMsg->set_sessionid(m_dwSessionId);
     }
     switch(pChatMsg->type())
     {
     case MOT_SYSTEM:
     {
         MsgObjSystem * pMsgObj = new MsgObjSystem();
         pMsgObj->set_type(((MsgText*)m_MsgObjBase)->type);
         pMsgObj->set_msg(((MsgText*)m_MsgObjBase)->msg);
//         pChatMsg->mutable_objsystem();
         pChatMsg->set_allocated_objsystem(pMsgObj);
         break;
     }
     case MOT_TEXT:
     {
         MsgObjText * pMsgObj = new MsgObjText();
         pMsgObj->set_type(((MsgText*)m_MsgObjBase)->type);
         pMsgObj->set_msg(((MsgText*)m_MsgObjBase)->msg);
//         pChatMsg->mutable_objtext();
         pChatMsg->set_allocated_objtext(pMsgObj);
         break;
     }
     case MOT_IMAGE:
     {
         MsgObjImage * pMsgObj = new MsgObjImage();
         pMsgObj->set_w(((MsgImage*)m_MsgObjBase)->w);
         pMsgObj->set_h(((MsgImage*)m_MsgObjBase)->h);
         pMsgObj->set_h(((MsgImage*)m_MsgObjBase)->h);
         pMsgObj->set_url(((MsgImage*)m_MsgObjBase)->url);
         pMsgObj->set_thumbnailurl(((MsgImage*)m_MsgObjBase)->thumbnailUrl);
//         pChatMsg->mutable_objimage();
         pChatMsg->set_allocated_objimage(pMsgObj);
         break;
     }
     default:
         break;
     }
 
     string buff = "";
     pChatMsg->SerializeToString(&buff);
 //    Logger.Log(INFO, "CGroupMsgSend cmd=0x%04x pChatMsg.sessionid=%d", m_wCmd, pChatMsg->sessionid());
 
 ///////////////////////////////////////////////////////////
     if( dwSize < dwUsedSize + (int)buff.size())
     {
         return ERR_NO_MORE_DATA;
     }
 
     int nRet = 0;
     if( 0 > ( nRet = CMsgBase::Encrypt((const char*)buff.c_str(), (uint32)buff.size(), (char*)p, dwSize-dwUsedSize )))
     {
         Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Encrypt failed", m_wCmd, m_dwId);
         return ERR_FAILED;
     }
 
     p += nRet;
     dwSize = m_dwLen = (int32)(p - pBuf);
     UpdateLen(pBuf, dwSize);
     Logger.Log(ERROR, "CChatMsgRecv::Pack(out)");
 
     return ERR_SUCCESS;
 }
 
