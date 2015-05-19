/*
 * CCSGroupUserListRequest.cpp
 *
 *  Created on: 2015年4月9日
 *      Author: hhq163
 */


#include "Common.h"
#include "Log.h"
#include "GroupUserListRequest.pb.h"
#include "CCSGroupUserListRequest.h"

CCSGroupUserListRequest::CCSGroupUserListRequest() {
    // TODO Auto-generated constructor stub

}

CCSGroupUserListRequest::~CCSGroupUserListRequest() {
    // TODO Auto-generated destructor stub
}

int CCSGroupUserListRequest::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(ERROR, "CCSGroupUserListRequest::Parse(in)");

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

    GroupUserListRequest *pGroupUserListRequest = new GroupUserListRequest();
    pGroupUserListRequest->Clear();

    if (pGroupUserListRequest->ParseFromString(strData))
    {
        if(pGroupUserListRequest->has_sessionid())
        {
            m_dwSessionId = pGroupUserListRequest->sessionid();
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
    Logger.Log(ERROR, "CCSGroupUserListRequest::Parse(out)");
    return ERR_SUCCESS;

}


int CCSGroupUserListRequest::Pack(uint8* pBuf, int32& dwSize)
{
    Logger.Log(ERROR, "CCSGroupUserListRequest::Pack(in)");
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

    GroupUserListRequest *pGroupUserListRequest = new GroupUserListRequest();
    pGroupUserListRequest->Clear();

    pGroupUserListRequest->set_sessionid(m_dwSessionId);


    string buff = "";
    pGroupUserListRequest->SerializeToString(&buff);
    Logger.Log(INFO, "CCSGroupUserListRequest cmd=0x%04x pGroupUserListRequest.sessionid=%d", m_wCmd, pGroupUserListRequest->sessionid());

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
    Logger.Log(ERROR, "CCSGroupUserListRequest::Pack(out)");

    return ERR_SUCCESS;
}

