/*
 * UndoTask.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: volt
 */

#include "UndoTask.h"

namespace expdb {

UndoTask::UndoTask(RowValue *value, int32_t size, int8_t flag, char *oldValue) :
		m_value(value), m_flag(flag), m_len(size), m_oldValue(oldValue) {

}

int32_t UndoTask::undo() {

	m_value->m_flag = m_flag;
	memcpy(m_value->m_value, m_oldValue, m_len);
	return SUCCESS;
}

UndoTask::~UndoTask() {

	if( m_oldValue != NULL ){
		VOLT_WARN("Memory leak here");
	}
}

Logger::Logger(Allocator &alloc, std::vector<UndoTask> &taskList) :
		m_alloc(alloc), m_taskList(taskList) {

}

int32_t Logger::undo(const RowDesc* desc, RowValue* value) {

	char *oldValue = (char *) m_alloc.alloc(desc->getRowLen());

	if (oldValue != NULL) {

		memcpy(oldValue, value->m_value, desc->getRowLen());

		UndoTask task(value, desc->getRowLen(), value->m_flag, oldValue);
		m_taskList.push_back(task);
		task.m_oldValue = NULL;

		return SUCCESS;
	} else {
		return ERROR;
	}
}

int32_t Logger::destroy(){

	for(std::vector<UndoTask>::iterator it = m_taskList.begin(); it != m_taskList.end(); it++){

		it->destroy(m_alloc);
	}
	return SUCCESS;
}

Logger::~Logger() {

	destroy();
}

} /* namespace expdb */
