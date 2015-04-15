/*
 * CCSGroupUserListGet.cpp
 *
 *  Created on: 2015年4月9日
 *      Author: hhq163
 */

#include "Common.h"
#include "Log.h"
#include "GroupUserListGet.pb.h"
#include "CCSGroupUserListGet.h"

CCSGroupUserListGet::CCSGroupUserListGet() {
    // TODO Auto-generated constructor stub

}

CCSGroupUserListGet::~CCSGroupUserListGet() {
    // TODO Auto-generated destructor stub
}

int CCSGroupUserListGet::Parse(uint8* pBuf, int32& dwSize)
{
    uint8* p = pBuf;
    int32 dwUsedSize = dwSize;
    Logger.Log(ERROR, "CCSGroupUserListGet::Parse(in)");

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

    GroupUserListGet *pGroupUserListGet = new GroupUserListGet();
    pGroupUserListGet->Clear();

    if (pGroupUserListGet->ParseFromString(strData))
    {
        if(pGroupUserListGet->has_groupsessionid())
        {
            m_dwSessionId = pGroupUserListGet->groupsessionid();
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
    Logger.Log(ERROR, "CCSGroupUserListGet::Parse(out)");
    return ERR_SUCCESS;

}


int CCSGroupUserListGet::Pack(uint8* pBuf, int32& dwSize)
{
    Logger.Log(ERROR, "CCSGroupUserListGet::Pack(in)");
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

    GroupUserListGet *pGroupUserListGet = new GroupUserListGet();
    pGroupUserListGet->Clear();

    pGroupUserListGet->set_groupsessionid(m_dwSessionId);


    string buff = "";
    pGroupUserListGet->SerializeToString(&buff);
    Logger.Log(INFO, "CCSGroupUserListGet cmd=0x%04x pGroupUserListGet.sessionid=%d", m_wCmd, pGroupUserListGet->groupsessionid());

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
    Logger.Log(ERROR, "CCSGroupUserListGet::Pack(out)");

    return ERR_SUCCESS;
}

