/*
 * hashidxtest.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: volt
 */

#include "test.h"
#include "../../common/index/HashIndex.h"
#include "../../common/murmur_hash.h"
using namespace expdb;

struct MyInt{
	uint64_t value;

	MyInt(int a){
		value = a;
	}

	uint64_t hash() const {
		return expdb::tools::murmurhash64A(&value, sizeof(value), 0);
	}

	bool operator ==(const MyInt &obj) const {

		return value == obj.value;
	}
};

int hashidxtest(int argc, char **argv){

	HashIndex<MyInt, int> myidx;

	myidx.init(32);

	myidx.insert(MyInt(1), 2);
	myidx.insert(MyInt(2),3);
	myidx.insert(MyInt(4),5);

	myidx.insert(MyInt(10),21);

	HashIndex<MyInt, int>::TableIterator it = myidx.begin();


	it.open();
	int value;
	while( it.next(value) != END ){
		printf("%d\n", value);
	}
	it.close();

	return 0;
}
//TEST(hashidxtest);
