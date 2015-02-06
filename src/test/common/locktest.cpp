#include "test.h"
#include "../../trans/QLock.h"
int testlock(int argc ,char **argv){

	expdb::QLock lock;

	int32_t ret;
	printf("state: %d\n", lock.getValue());

	ret = lock.lock();

	printf("invoke rc: %d, state: %d\n",ret, lock.getValue());

	ret = lock.lock();

	printf("invoke rc: %d, state: %d\n",ret, lock.getValue());

	ret = lock.unlock();

	printf("invoke rc: %d, state: %d\n",ret, lock.getValue());

	ret = lock.unlock();

	printf("invoke rc: %d, state: %d\n",ret, lock.getValue());

	ret = lock.lock();

	printf("invoke rc: %d, state: %d\n",ret, lock.getValue());


	return 0;
}
//TEST(testlock);
