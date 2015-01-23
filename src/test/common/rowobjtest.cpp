/*
 * rowobjtest.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: volt
 */
#include "test.h"
#include "../../storage/RowObj.h"

using namespace expdb;
int rowobjtest(int argc, char **argv) {

	RowObj obj;
	RowObj arg;

	obj.setBigInt(10);
	arg.setBigInt(20);

	obj = RowObj::op(ADD, obj, arg);
	obj.dump();

	obj = RowObj::op(ASSI, obj, arg);
	obj.dump();

	obj = RowObj::op(MIN, obj, arg);
	obj.dump();

	obj.setString("hello", 10);

	return 0;
}
TEST(rowobjtest);

