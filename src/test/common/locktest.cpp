#include "test.h"
#include <unistd.h>
#include <pthread.h>
#include "../../common.h"
#include "../../clock.h"
#include "../../trans/QLock.h"

using namespace expdb;
void *testLockHandler(void *arg) {

	QLock *lock = static_cast<QLock *>(arg);
	if ( NULL != lock) {

		while (true) {
			if (SUCCESS == lock->lock()) {
				VOLT_WARN("Thread[%lu] hold lock\n", lock->getOwner());
				lock->unlock();

//				long start = common::getCycleCount();
//				while( common::getCycleCount() - start < 10000 );
			}
		}
	}
	return NULL;
}

int testlock(int argc, char **argv) {

	expdb::QLock lock;


	pthread_t pid1, pid2;

	pthread_create(&pid1, NULL, testLockHandler, (void *)&lock);
	pthread_create(&pid2, NULL, testLockHandler, (void *)&lock);

	pthread_join(pid1, NULL);
//	pthread_join(pid2, NULL);

//	printf("state: %d\n", lock.getValue());
//
//	ret = lock.lock();
//
//	printf("invoke rc: %d, state: %d\n", ret, lock.getValue());
//
//	ret = lock.lock();
//
//	printf("invoke rc: %d, state: %d\n", ret, lock.getValue());
//
//	ret = lock.unlock();
//
//	printf("invoke rc: %d, state: %d\n", ret, lock.getValue());
//
//	ret = lock.unlock();
//
//	printf("invoke rc: %d, state: %d\n", ret, lock.getValue());
//
//	ret = lock.lock();
//
//	printf("invoke rc: %d, state: %d\n", ret, lock.getValue());

	return 0;
}
//TEST(testlock);
