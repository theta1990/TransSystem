/*
 * rowtest.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: volt
 */

#include "test.h"
#include "../../storage/Row.h"
#include "../../storage/RowObj.h"

#include "../../common/serialization.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace expdb;

int rowtest(int argc, char **argv){


	RowDesc des;
	RowObj obj;
	RowObj obj2;
	char buf[1024];
	int64_t size = 1024;
	int64_t pos = 0;
	int64_t stpos = 0;

	obj.setSmallInt(20);
	obj2.setMidInt(40);

	des.addRowType(SMALLINT);
	des.addRowType(MIDINT);
	Row row(&des);
	Row row2(&des);
	const RowDesc * cdes = &des;

	row.setDesc(cdes);
	row2.setDesc(cdes);

	row.addCol(obj, 1);
	row.addCol(obj2,2);

	row.serilization(buf, size, pos);

	row2.deserilization(buf, size, stpos);

	printf("serilization size: %d\n", pos);
	row2.dump();
	return 0;
}
//TEST(rowtest);
//testfunc func = rowtest;
