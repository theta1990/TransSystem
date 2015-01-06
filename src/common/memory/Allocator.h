/*
 * Allocator.h
 *
 *  Created on: Dec 12, 2014
 *      Author: volt
 */

#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
#include "../../common.h"
#include <assert.h>
#include "../atomic.h"
namespace expdb {

class Allocator {

	const static uint64_t DEFALUT_POOL_SIZE = 1024L*1024L*1024L;		//1G bytes
public:
	Allocator();
//	Allocator(uint64_t allocSize);
	virtual ~Allocator();
	void init(uint32_t allocSize);
	inline void *alloc(int32_t sz = 0);	//it should be thread safe
	inline void free(void *ptr);

private:
	char *m_storage;
	uint64_t m_size;
	uint32_t m_allocSize;
	volatile uint64_t m_offset;
};

inline void* expdb::Allocator::alloc(int32_t sz) {

	void *ptr = NULL;
	uint64_t off = sz;
	if (sz == 0)
		sz = m_allocSize;
	assert(sz > 0);
	if(m_storage == NULL ){
		VOLT_ERROR("Memory pool not inited");
	}else if (m_offset + sz > m_size) {
		VOLT_ERROR("Memory pool out of size");
	} else {
		off = atomic::atomic_add(&m_offset, off);
		if (off + sz > m_size) {
			VOLT_ERROR("Memory pool out of size");
		} else {
			ptr = m_storage + off;
		}
	}
	return ptr;
}

inline void expdb::Allocator::free(void* ptr) {

}

} /* namespace expdb */

#endif /* ALLOCATOR_H_ */
