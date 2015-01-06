/*
 * test.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#include "test.h"
#include "../../storage/SchemaMgr.h"

using namespace expdb;

void initSchema(){

	SchemaMgr* schema = SchemaMgr::getInstance();
	RowDesc desc;
	const RowDesc *tableSche;
	desc.addRowType(SMALLINT);
	desc.addRowType(MIDINT);

	schema->addTable("hw", &desc);

	schema->getTableDesc("hw", tableSche);

	tableSche->dump();

	printf("---------------------------------\n");
	printf("----------start test-------------\n");
	printf("---------------------------------\n");
}

int main(int argc, char **argv){

	initSchema();
	func(argc, argv);
	return 0;
}


