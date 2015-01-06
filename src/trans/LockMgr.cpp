/*
 * LockMgr.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#include "LockMgr.h"
#include "../debuglog.h"
#include <string.h>
#include <stdlib.h>
namespace expdb {

LockMgr::LockMgr(unsigned int lockCount) :
		m_lockCount(lockCount) {
	// TODO Auto-generated constructor stub
	memset(m_lockTable, 0, sizeof(m_lockTable));
}

int LockMgr::acquireLock(const unsigned int tranId, unsigned int lockId) {

	int ret = SUCCESS;
	unsigned int oldValue;

	if (lockId >= m_lockCount) {

		ret = OUT_OF_RANGE;
		VOLT_ERROR("lock[%d] out of range", lockId);
	} else if (tranId == (oldValue = m_lockTable[lockId])) {

		VOLT_DEBUG("lock is acquired");
	} else if (0 == oldValue) {

		//atomic update the lock owner
		if (__sync_bool_compare_and_swap(&m_lockTable[lockId], oldValue,
				tranId))
//		if( m_lockTable[lockId] == oldValue )
		{
//			m_lockTable[lockId] = tranId;
			ret = SUCCESS;
		} else {

			ret = ATOMIC_UPDATE_FAIL;
			VOLT_ERROR("Lock failed oldState[%d], newState[%d]", oldValue, m_lockTable[lockId]);
		}
	} else {

		ret = LOCK_NOT_FREE;
		VOLT_WARN("lock[%d] occupied, trans[%d] conflict with trans[%d]",lockId, tranId, oldValue);
	}
	return ret;
}

int LockMgr::releaseLock(const unsigned int tranId, unsigned int lockId) {

	int ret = SUCCESS;
	unsigned int oldValue;
	if (lockId >= m_lockCount) {

		ret = OUT_OF_RANGE;
	} else if (tranId == (oldValue = m_lockTable[lockId])) {

		if (__sync_bool_compare_and_swap(&m_lockTable[lockId], oldValue, 0)) {

			ret = SUCCESS;
			VOLT_DEBUG("lock %d released by trans %d", lockId, tranId);
		} else {

			ret = ATOMIC_UPDATE_FAIL;
			VOLT_ERROR("lock %d realease failed", lockId);
		}
	} else {

		ret = LOCK_NOT_OWNED;
		VOLT_ERROR("lock %d realeased failed, not owned", lockId);
	}
	return ret;
}

LockMgr::~LockMgr() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */
