/*
 * CMsgNotify.cpp
 */
#include "Common.h"
#include "Log.h"
#include "CMsgNotify.h"
#include "Common.pb.h"

CMsgNotify::CMsgNotify()
{
    m_dwMessageType = 0;
    m_dwpushType = 0;
    m_dwEventType = 0;
    m_llMessageExpires = 0;
}

CMsgNotify::~CMsgNotify()
{
    Push_Payload* payload = NULL;
    for(int i = 0; i < m_PayloadList.size(); i++)
    {
        payload = m_PayloadList[i];
        if(payload != NULL)
        {
            delete payload;
            payload = NULL;
        }
    }
}


int CMsgNotify::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(ERROR, "CMsgNotify::Parse(in)");

    int iErr = CMsgBase::Parse(pBuf, dwUsedSize);
    if(ERR_SUCCESS != iErr)
    {
        return iErr;
    }
    p += dwUsedSize;


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

    Push *pMsg = new Push();
    pMsg->Clear();

    if (pMsg->ParseFromString(strData))
    {
        if(pMsg->has_pushtype())
        {
            m_dwpushType = pMsg->pushtype();
        }
        if(pMsg->has_messagetype())
        {
            m_dwMessageType = pMsg->messagetype();
        }
        if(pMsg->has_messageexpires())
        {
            m_llMessageExpires = pMsg->messageexpires();
        }

        if(pMsg->has_eventtype())
        {
            m_dwEventType = pMsg->eventtype();
        }

        //解析uidlist
        for(int i = 0; i < pMsg->uidlist_size(); i++)
        {
            m_mapUidList[i] = pMsg->uidlist(i);
            Logger.Log(INFO, "uidlist[%d]:[%d]", i, m_mapUidList[i]);
        }
        //解析payload
        for(int i = 0; i < pMsg->payload_size(); i++)
        {
            Push_Payload* payload = new Push_Payload();

            if(pMsg->payload(i).has_title())
            {
                payload->set_title(pMsg->payload(i).title());
                Logger.Log(INFO, "PayloadList[%d]->title:[%s]", i, pMsg->payload(i).title().c_str());
            }
            if(pMsg->payload(i).has_description())
            {
                payload->set_description(pMsg->payload(i).description());
                Logger.Log(INFO, "PayloadList[%d]->description:[%s]", i, pMsg->payload(i).description().c_str());
            }

            for(int k = 0; k < pMsg->payload(i).extendedparameter_size(); k++)
            {

                Push_Payload_ExtendedParameter* extendedParameter = payload->add_extendedparameter();
                if(pMsg->payload(i).extendedparameter(k).has_key())
                {
                    extendedParameter->set_key(pMsg->payload(i).extendedparameter(k).key());
                    extendedParameter->set_val(pMsg->payload(i).extendedparameter(k).val());
                }
            }

            m_PayloadList[i] = payload;
        }

        Logger.Log(INFO, "cmd:[0x%04x] m_dwDesUid:[%lld] m_dwSessionId:[%d]", m_wCmd, m_dwId, m_dwSessionId);
    }
    else
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_dwDesUid:%lld Json parse  failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }
//////////////////////////////////////////////////////////////////////////
    p += m_Buflen;

    dwSize = (int32)(p - pBuf );
    Logger.Log(ERROR, "CMsgNotify::Parse(out)");
    return ERR_SUCCESS;

}


int CMsgNotify::Pack(uint8* pBuf, int32& dwSize)
{
    Logger.Log(ERROR, "CMsgNotify::Pack(in)");
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

    Push *pMsg = new Push();
    pMsg->Clear();

    pMsg->set_pushtype((PushType)m_dwpushType);
    pMsg->set_messagetype((MessageType)m_dwMessageType);
    pMsg->set_messageexpires(m_llMessageExpires);
    pMsg->set_eventtype((EventType)m_dwEventType);

    for(int i = 0; i < m_mapUidList.size(); i++)
    {
        pMsg->add_uidlist(m_mapUidList[i]);
    }

    for(int i = 0; i < m_PayloadList.size(); i++)
    {
        Push_Payload* payload = pMsg->add_payload();
        if(m_PayloadList[i]->has_title())
        {
            payload->set_title(m_PayloadList[i]->title());
        }
        if(m_PayloadList[i]->has_description())
        {
            payload->set_description(m_PayloadList[i]->description());
        }

        for(int k=0; k < m_PayloadList[i]->extendedparameter_size(); k++)
        {
            Push_Payload_ExtendedParameter* extendedParameter = payload->add_extendedparameter();
            if(m_PayloadList[i]->extendedparameter(k).has_key())
            {
                extendedParameter->set_key(m_PayloadList[i]->extendedparameter(k).key());
            }
            if(m_PayloadList[i]->extendedparameter(k).has_val())
            {
                extendedParameter->set_val(m_PayloadList[i]->extendedparameter(k).val());
            }
        }
    }

    string buff = "";
    pMsg->SerializeToString(&buff);
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
    Logger.Log(ERROR, "CMsgNotify::Pack(out)");

    return ERR_SUCCESS;
}

