/*
 * QLock.h
 *
 *  Created on: Dec 16, 2014
 *      Author: volt
 */

#ifndef QLOCK_H_
#define QLOCK_H_

#include "../common.h"
#include <assert.h>
namespace expdb {

/**
 * Lock structure
 */
class QLock {
public:
	QLock();

	int32_t try_lock();
	int32_t lock();
	int32_t lock_block();
	int32_t unlock();
	int32_t reset();

	uint8_t getValue(){
		return m_lock;
	}

	pid_t getOwner(){
		return m_owner;
	}

	virtual ~QLock();

private:

	volatile uint8_t	m_lock;
	pid_t		m_owner;
	const static uint64_t m_TIMEOUT = 1000;
};

class ScopedLock{

public:
	inline ScopedLock(QLock &lock) : m_lock(lock){
		assert( SUCCESS == m_lock.lock_block());
	}

	inline ~ScopedLock(){
		assert( SUCCESS == m_lock.unlock());
	}
private:
	QLock &m_lock;
};

} /* namespace expdb */

#endif /* QLOCK_H_ */
