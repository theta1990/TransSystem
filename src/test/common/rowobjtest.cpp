/*
 * rowobjtest.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: volt
 */
#include "test.h"
#include "../../storage/RowObj.h"
#include <vector>

using namespace expdb;
int rowobjtest(int argc, char **argv) {

	RowObj obj;
	RowObj arg;

	obj.setBigInt(10);
	arg.setBigInt(20);

	obj = RowObj::op(ADD, obj, arg);
//	obj.dump();

	obj = RowObj::op(ASSI, obj, arg);
//	obj.dump();

	obj = RowObj::op(MIN, obj, arg);
//	obj.dump();

	obj.setString("hello", 10);

	obj.dump();
	printf("\n");
	arg = obj;
	obj.clear();
	arg.dump();
	printf("\n");

	RowObj obj2(arg);

	obj2.dump();

	std::vector<RowObj> list;
	list.push_back(RowObj("rand", 10));
	list.push_back(RowObj("rand", 10));
	list.push_back(RowObj("rand", 10));
	list.push_back(RowObj("rand", 10));

	list.clear();

	RowObj dd(0.4);
	RowObj cc(-9.1);
	RowObj andd = RowObj::op(ADD, dd, cc);

	dd.dump();

	printf("\n");

	andd.dump();
	printf("\n");

	return 0;
}
//TEST(rowobjtest);

