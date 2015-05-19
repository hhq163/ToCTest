/*
 * CMsgPush.cpp
 *
 *  Created on: 2015年4月20日
 *      Author: kevent
 */


#include "Common.h"
#include "Log.h"
#include "CMsgPush.h"

CMsgPush::CMsgPush()
{
    for(int i = 0; i < PAGE_SIZE; i++)
    {
        m_MsgArray[i] = NULL;
    }
    m_dwMsgCount = 0;
    tmp = NULL;
}

CMsgPush::~CMsgPush()
{
    for(int i = 0; i < m_dwMsgCount; i++)
    {
        if(m_MsgArray[i] != NULL)
        {
            uint8 *p = m_MsgArray[i]->pMsg;
            m_MsgArray[i]->pMsg = NULL;
            if(m_MsgArray[i]->pMsg != NULL)
            {
                delete[] p;
                p = NULL;
            }
            delete m_MsgArray[i];
            m_MsgArray[i] = NULL;
        }
    }
}

MSG_ARRAY_T* CMsgPush::NewMsgArray(int32 dwSize)
{
    tmp = NULL;
    tmp = new MSG_ARRAY_T();
    tmp->len = 0;
    tmp->pMsg = new uint8[dwSize];
    memset(tmp->pMsg, 0x00, sizeof(tmp->pMsg));
    return tmp;
}

/**
 * 消息包解析
 */
int CMsgPush::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;

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

    /*
        check if need  Decrypt , ver??
    */
    int nRet = 0;
    char* pdata = NULL;
    if( 0 > ( nRet = CMsgBase::Decrypt((const char*)p, m_dwLen - dwUsedSize, pdata, m_Buflen)))
    {
        Logger.Log(ERROR, "cmd:[0x%04x]  m_dwId:%lld Decrypt failed", m_wCmd,m_dwId);
        return ERR_FAILED;
    }
    CHECK_IF_NULL(pdata);

//////////////////////////////////////////////////////////////////////////
    Logger.Log(ERROR, "###################CMsgPush::Parse cmd:[0x%04x]  m_dwId:%u ", m_wCmd, m_dwId);
    int i;
    m_dwMsgCount = 0;

    for(i = 0; i < m_dwLen - dwUsedSize; i += m_MsgArray[m_dwMsgCount++]->len)
    {
        uint32 len    = ntohl(*((uint32*)pdata));//包头第一个字段为包长度
        m_MsgArray[m_dwMsgCount] = NewMsgArray(len + 1);
        m_MsgArray[m_dwMsgCount]->len = len;
        memcpy(m_MsgArray[m_dwMsgCount]->pMsg, pdata, m_MsgArray[m_dwMsgCount]->len);
        pdata += m_MsgArray[m_dwMsgCount]->len;

        Logger.Log(ERROR, "m_MsgArray[%d]->len = %u, m_dwMsgCount=%d", m_dwMsgCount, m_MsgArray[m_dwMsgCount]->len, m_dwMsgCount);
    }

//////////////////////////////////////////////////////////////////////////
    p += i;

    dwSize = (int32)(p - pBuf);
    return ERR_SUCCESS;

}


int CMsgPush::Pack(uint8* pBuf, int32& dwSize)
{
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

    uint8 buff[MAX_BUFFER_SIZE] = {'\0'};
    int32 buff_size = 0;
    Logger.Log(ERROR, "CMsgPush::Pack m_dwMsgCount = %d", m_dwMsgCount);
    for(int i = 0; i < m_dwMsgCount; i++)
    {
        //整包长度在外面通过控制m_dwMsgCount控制
        memcpy(buff + buff_size, m_MsgArray[i]->pMsg, m_MsgArray[i]->len);
        buff_size += m_MsgArray[i]->len;
        Logger.Log(ERROR, "CMsgPush::Pack buff_size = %d", buff_size);
    }


    if( dwSize < dwUsedSize + (int)buff_size)
    {
        return ERR_NO_MORE_DATA;
    }

    int nRet = 0;
    if( 0 > ( nRet = CMsgBase::Encrypt((const char*)buff, buff_size, (char*)p, dwSize-buff_size )))
    {
        Logger.Log(ERROR, "cmd:[0x%04x] m_llDesUid:%lld Encrypt failed", m_wCmd, m_dwId);
        return ERR_FAILED;
    }

    p += nRet;

    dwSize = m_dwLen = dwUsedSize + buff_size;
    Logger.Log(ERROR, "CMsgPush::Pack totallen = %d", dwSize);

    UpdateLen(pBuf, dwSize);

    return ERR_SUCCESS;
}






