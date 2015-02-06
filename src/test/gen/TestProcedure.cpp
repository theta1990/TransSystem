/*
 * TestProcedure.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: volt
 */

#include "TestProcedure.h"

namespace expdb {

StoredProcedure * AddProcedure::_ins = NULL;
StoredProcedure * TransferTask::_ins = NULL;

AddProcedure::AddProcedure(){

}

TransferTask::TransferTask(){

}

StoredProcedure* AddProcedure::getInstance() {

	if (_ins == NULL) {
		_ins = new AddProcedure();
	}
	return _ins;
}

StoredProcedure* TransferTask::getInstance() {
	if( _ins == NULL  ){
		_ins = new TransferTask();
	}
	return _ins;
}

} /* namespace expdb */
