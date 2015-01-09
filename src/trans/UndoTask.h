/*
 * UndoTask.h
 *
 *  Created on: Jan 8, 2015
 *      Author: volt
 */

#ifndef UNDOTASK_H_
#define UNDOTASK_H_

#include "../storage/RowTable.h"

namespace expdb {

class UndoTask {
public:
	UndoTask(RowValue *value);

	int32_t undo();

	virtual ~UndoTask();

private:

};

} /* namespace expdb */

#endif /* UNDOTASK_H_ */
