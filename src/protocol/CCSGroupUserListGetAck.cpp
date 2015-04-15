/*
 * CCSGroupUserListGetAckAck.cpp
 *
 *  Created on: 2015年4月9日
 *      Author: hhq163
 */

#include "Common.h"
#include "Log.h"
#include "GroupUserListGetAck.pb.h"
#include "CCSGroupUserListGetAck.h"

CCSGroupUserListGetAck::CCSGroupUserListGetAck() {
    // TODO Auto-generated constructor stub

}

CCSGroupUserListGetAck::~CCSGroupUserListGetAck() {
    // TODO Auto-generated destructor stub
}

int CCSGroupUserListGetAck::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(INFO, "CCSGroupUserListGetAck::Parse(in)");

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

    GroupUserListGetAck *pGroupUserListGet = new GroupUserListGetAck();
    pGroupUserListGet->Clear();

    if (pGroupUserListGet->ParseFromString(strData))
    {
        if(pGroupUserListGet->has_sessionid())
        {
            m_dwSessionId = pGroupUserListGet->sessionid();
        }
        //解析uid
        for(int i = 0; i < pGroupUserListGet->uid_size(); i++)
        {
            const int32& uid = pGroupUserListGet->uid(i);
            m_mapuidlist[i] = uid;
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
    Logger.Log(ERROR, "CCSGroupUserListGetAck::Parse(out)");
    return ERR_SUCCESS;

}


int CCSGroupUserListGetAck::Pack(uint8* pBuf, int32& dwSize)
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

    GroupUserListGetAck *pGroupUserListGet = new GroupUserListGetAck();
    pGroupUserListGet->Clear();

    pGroupUserListGet->set_sessionid(m_dwSessionId);
    for(int i = 0; i < m_mapuidlist.size(); i++)
    {
        pGroupUserListGet->add_uid(m_mapuidlist[i]);
    }

    string buff = "";
    pGroupUserListGet->SerializeToString(&buff);

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
    Logger.Log(INFO, "CCSGroupUserListGetAck::Pack(out)");

    return ERR_SUCCESS;
}
