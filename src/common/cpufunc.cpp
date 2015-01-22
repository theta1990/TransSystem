/*
 * cpufunc.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: volt
 */
#include <pthread.h>
#include <unistd.h>
#include "cpufunc.h"

inline int32_t setAffinity(int32_t id) {

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(id, &set);
	return sched_setaffinity(getpid(), 1, &set);
}



