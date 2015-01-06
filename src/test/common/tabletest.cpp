/*
 * tabletest.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: volt
 */
#include "test.h"
#include "../../storage/RowTable.h"
#include "../../storage/SchemaMgr.h"
#include <vector>
using namespace expdb;

int rowGen(Row &row) {

	const RowDesc *desc;
	SchemaMgr::getInstance()->getTableDesc("hw", desc);

	row.setDesc(desc);

	for (uint32_t i = 0; i < desc->getColCnt(); ++i) {

		RowType type = desc->getRowtype(i);
		RowObj obj;
		switch (type) {
		case SMALLINT:
			obj.setSmallInt(rand() % 100);
			break;
		case MIDINT:
			obj.setMidInt(rand() % 100);
			break;
		case BIGINT:
			obj.setBigInt(rand() % 100);
			break;
		case CHAR:
			obj.setChar(rand() % ('z' - 'a' + 1) + 'a');
			break;
		default:
			VOLT_ERROR("type %s not supported now", TypeName[type])
			;
		}
		row.addCol(obj, i);
	}
	return 0;
}

void *worker(void *arg) {

	RowTable *table = static_cast<RowTable*>(arg);
	Row row;
	RowKey key;
	std::vector<RowKey> *keys = new std::vector<RowKey>();

	printf("create keys %x\n", keys);

	for (int i = 0; i < 200; ++i) {
		rowGen(row);
		row.getRowKey(key);
//		row.dump();
		if (SUCCESS == table->insert(key, row)) {
			keys->push_back(key);
		}
	}
	return keys;
}

int tabletest(int argc, char **argv) {

	RowTable table;
	pthread_t tid1, tid2;


	std::vector<RowKey> *keys1, *keys2;
	const RowDesc * desc;

	if (SUCCESS == SchemaMgr::getInstance()->getTableDesc("hw", desc)) {
		table.setDesc(desc);
	}
	Row row(desc);
	pthread_create(&tid1, NULL, worker, &table);

	pthread_create(&tid2, NULL, worker, &table);

	if (0 == pthread_join(tid1, (void **) &keys1)) {
		printf("thread1 joined\n");
		printf("-keys %x\n", keys1);
	}
	if (0 == pthread_join(tid2, (void **) &keys2)) {
		printf("thread2 joined\n");
		printf("-keys %x\n", keys2);
	}

	printf("Row inserted by thread1\n");
	for (uint32_t i = 0; i < keys1->size(); ++i) {
		if (SUCCESS == table.get((*keys1)[i], row)) {
//			row.dump();
		} else {
			VOLT_ERROR("error read");
		}
	}
	printf("Row inserted by thread2\n");
	for (uint32_t i = 0; i < keys2->size(); ++i) {
		if (SUCCESS == table.get((*keys2)[i], row)) {
//			row.dump();
		}else {
			VOLT_ERROR("error read");
		}
	}
	return 0;
}
//TEST(tabletest);

