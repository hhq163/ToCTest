/*
 * ModuleMgr.cpp
 *
 *  Created on: May 9, 2015
 *      Author: hhq163
 */

#include "Common.h"
#include "Log.h"
#include "ModuleMgr.h"

ModuleMgr::ModuleMgr() {
    // TODO Auto-generated constructor stub

}

ModuleMgr::~ModuleMgr() {
    // TODO Auto-generated destructor stub
}
/**
 * 处理同步返回消息
 */
int ModuleMgr::HandleSyncMsgAck(CMsgBase* pMsg){
    Logger.Log(DEBUG, "HandleSyncMsgAck (in)");


    Logger.Log(DEBUG, "HandleSyncMsgAck (out)");

    return ERR_FAILED;
}
