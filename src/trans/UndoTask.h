/*
 * UndoTask.h
 *
 *  Created on: Jan 8, 2015
 *      Author: volt
 */

#ifndef UNDOTASK_H_
#define UNDOTASK_H_

#include "../storage/RowTable.h"
#include <vector>

namespace expdb {

class UndoTask {
public:
	UndoTask(RowValue *value, int32_t len, int8_t flag, char *oldValue);

	int32_t undo();
	int32_t destroy(Allocator &alloc){
		if( m_oldValue != NULL ){
			alloc.free(m_oldValue);
			m_oldValue = NULL;
		}
		return SUCCESS;
	}

	virtual ~UndoTask();

private:

	RowValue *m_value;
	int8_t m_flag;
	int32_t	m_len;
	char *	m_oldValue;
};


class Logger{
public:
	Logger(Allocator &alloc, std::vector<UndoTask> &taskList);

	int32_t undo(const RowDesc *desc, RowValue *oldValue);

	int32_t destroy();
	virtual ~Logger();
private:

	Allocator& 				m_alloc;
	std::vector<UndoTask> 	&m_taskList;

};

} /* namespace expdb */

#endif /* UNDOTASK_H_ */
