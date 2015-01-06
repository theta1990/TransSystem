/*
 * TaskQueue.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#include "TaskQueue.h"
#include "../common.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

namespace expdb {

TaskQueue::TaskQueue() : m_pid(0) {

}

void* TaskQueue::run(void *arg) {

	TaskQueue* _ins = (TaskQueue*)arg;
	_ins ->work();
	return NULL;
}

void TaskQueue::start() {

	pthread_create(&m_pid, NULL, &run, this);
	VOLT_INFO("thread %d start\n", m_pid);
}


void TaskQueue::join() {

	pthread_join(m_pid, NULL);
}

TaskQueue::~TaskQueue() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */

