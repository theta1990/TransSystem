/*
 * LockMgr.h
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#ifndef LOCKMGR_H_
#define LOCKMGR_H_

#include "../common.h"

namespace expdb {
/**
 * 应该不能采用集中是的锁管理方式，还是要将锁信息分散到每个数据项中。
 */
class LockMgr {
public:
	LockMgr(unsigned int lockCount);

	int acquireLock(const unsigned int tranId, unsigned int lockId);
	int releaseLock(const unsigned int tranId, unsigned int lockId);
	virtual ~LockMgr();

private:

	unsigned int m_lockTable[TABLESIZE];
	unsigned int m_lockCount;
};

} /* namespace expdb */

#endif /* LOCKMGR_H_ */
