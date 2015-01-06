/*
 * common.h
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#ifndef COMMON_H_
#define COMMON_H_
#include <stdio.h>
#include <stdint.h>
#include "debuglog.h"

#define TABLESIZE 0xffffff
#define UNUSED(x) (void*)x
namespace expdb {
enum RETVALUE {
	SUCCESS,
	ERROR,
	ATOMIC_UPDATE_FAIL,
	LOCK_NOT_FREE,
	LOCK_NOT_OWNED,
	OUT_OF_RANGE,
	NOT_EXIST,
	TRAN_FINISHED,
	TRAN_SUSPEND,
	LOCKISFREE,
	DUPKEY,
	NOTFOUND,
	END
};
}

#endif /* COMMON_H_ */
