/*
 * ModuleMgr.h
 *
 *  Created on: May 9, 2015
 *      Author: hhq163
 */

#ifndef SRC_MSGSYSTEM_MODULEMGR_H_
#define SRC_MSGSYSTEM_MODULEMGR_H_

/*
 *
 */
class ModuleMgr {
public:
    ModuleMgr();
    virtual ~ModuleMgr();

public:
    int     HandleSyncMsgAck(CMsgBase* pMsg);
};

#endif /* SRC_MSGSYSTEM_MODULEMGR_H_ */
