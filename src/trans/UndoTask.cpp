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
	// TODO Auto-generated destructor stub
}

Logger::Logger(std::vector<UndoTask> &taskList) :
		m_alloc(), m_taskList(taskList) {

	m_alloc.init(0);
}

int32_t Logger::undo(const RowDesc* desc, RowValue* value) {

	char *oldValue = (char *) m_alloc.alloc(desc->getRowLen());

	if (oldValue != NULL) {

		memcpy(oldValue, value->m_value, desc->getRowLen());

		m_taskList.push_back(
				UndoTask(value, desc->getRowLen(), value->m_flag, oldValue));
		return SUCCESS;
	} else {
		return ERROR;
	}
}

Logger::~Logger() {
}

} /* namespace expdb */
