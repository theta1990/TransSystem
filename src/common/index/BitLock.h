/*
 * BitLock.h
 *
 *  Created on: Dec 11, 2014
 *      Author: volt
 */

#ifndef BITLOCK_H_
#define BITLOCK_H_

#include "../../common.h"
#include "../atomic.h"
#include <stdlib.h>
#include <string.h>
namespace expdb {

static const uint8_t BIT_MASKS[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
		0x80 };

class BitLock {
public:
	BitLock();
	virtual ~BitLock();

public:

	inline int init(const int64_t size);
	inline void destroy();
	inline int lock(const uint64_t index);
	inline int unlock(const uint64_t index);
private:
	uint64_t m_size;
	uint8_t * volatile m_bits;
};

class BitLockGuard {

public:
	BitLockGuard(BitLock &lock, const uint64_t index) :
			m_lock(lock), m_index(index) {

		m_lock.lock(m_index);
	}

	~BitLockGuard() {

		m_lock.unlock(m_index);
	}

private:
	BitLock &m_lock;
	const uint64_t m_index;
};

inline int64_t upper_align(int64_t input, int64_t align) {

	int64_t ret = input;
	ret = (input + align - 1) & ~(align - 1);
	return ret;
}

int BitLock::init(const int64_t size) {

	int ret = SUCCESS;

	if (0 < m_size || NULL != m_bits)
		return expdb::ERROR;
	else if (0 >= size)
		return expdb::ERROR;
	else {

		int64_t byte_size = upper_align(size, 8) / 8;
		if ( NULL == (m_bits = (uint8_t *)malloc(byte_size))) {
			ret = expdb::ERROR;
		} else {

			memset(m_bits, 0, byte_size);
			m_size = size;
		}
	}
	return ret;
}

void BitLock::destroy() {

	if ( NULL != m_bits) {
		free(m_bits);
	}
	m_size = 0;
	m_bits = NULL;
}

int BitLock::lock(const uint64_t index) {

//locate the bit lock
	int ret = SUCCESS;
	uint8_t oldValue;
	uint64_t bytePos = index / 8;
	uint64_t bitPos = index % 8;

	if (m_size < 0 || m_bits == NULL)
		ret = expdb::ERROR;

	else if (index >= m_size)
		ret = expdb::ERROR;

	else {
		do {
			oldValue = m_bits[bytePos];

			if ((oldValue & BIT_MASKS[bitPos]))
				continue;	//lock is hold by other thread

		} while (oldValue != atomic::atomic_compare_exchange(&m_bits[bytePos], oldValue,
				oldValue | BIT_MASKS[bitPos]));
	}
	return ret;
}

int BitLock::unlock(const uint64_t index) {

	int ret = SUCCESS;
	uint8_t oldValue;
	uint64_t bytePos = index / 8;
	uint64_t bitPos = index % 8;

	if (m_size < 0 || m_bits == NULL)
		ret = expdb::ERROR;

	else if (index >= m_size)
		ret = expdb::ERROR;

	else {
		do {
			oldValue = m_bits[bytePos];

			if (!(oldValue & BIT_MASKS[bitPos])) {

				ret = expdb::LOCKISFREE;
				break;	//lock is hold by other thread
			}

		} while (!atomic::atomic_compare_exchange(&m_bits[bytePos], oldValue,
				oldValue | BIT_MASKS[bitPos]));
	}
	return ret;
}

} /* namespace expdb */

#endif /* BITLOCK_H_ */
