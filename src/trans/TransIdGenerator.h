/*
 * TransIdGenerator.h
 *
 *  Created on: Feb 10, 2015
 *      Author: volt
 */

#ifndef TRANSIDGENERATOR_H_
#define TRANSIDGENERATOR_H_
#include "../common.h"
#include "../common/atomic.h"
namespace expdb {

class TransIdGenerator {
public:
	TransIdGenerator();
	virtual ~TransIdGenerator();

	static uint32_t getId() {

		return atomic::atomic_inc(&globalId);
	}

private:
	static volatile uint32_t globalId;
};

} /* namespace expdb */

#endif /* TRANSIDGENERATOR_H_ */
