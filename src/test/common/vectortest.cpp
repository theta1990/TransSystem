#include "test.h"
#include <stdio.h>
#include <vector>
class Obj{
public:
	Obj(){
		id = a++;
	}

	virtual ~Obj(){
		printf("test %d \n", id);
	}
private:
	static int a;
	int id;
};

int Obj::a = 1;

int testvector(int argc, char **argv){

	int ret = 0;

	std::vector<Obj> list;
	Obj o1,o2,o3,o4;
	list.push_back(o1);
	list.push_back(o2);
	list.push_back(o3);
	list.push_back(o4);

	return ret;
}
//TEST(testvector);
