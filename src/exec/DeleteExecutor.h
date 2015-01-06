/*
 * DeleteExecutor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#ifndef DELETEEXECUTOR_H_
#define DELETEEXECUTOR_H_

#include "Executor.h"


namespace expdb {

class DeleteExecutor : public Executor {

public:
	ExecType getType(){
		return DELETE;
	}

	int32_t setPara();

private:
};

} /* namespace expdb */

#endif /* DELETEEXECUTOR_H_ */
