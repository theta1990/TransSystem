/*
 * memorypooltest.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: volt
 */

#include "test.h"
#include <pthread.h>
#include <stdlib.h>
#include "../../common.h"
#include "../../clock.h"

void *memoryThread(void *arg) {

	void *p = NULL;
//	int32_t step = *(int32_t*) arg;
//	int32_t size = *(int32_t*) arg;
	uint64_t begin, end, final = 0;
	uint32_t iter = 1024;
	void *store[1024];
	uint8_t sizeList[1024];
	uint8_t allRound = 128;
	uint8_t round = allRound;
	while (round--) {

		for (uint32_t i = 0; i < iter; ++i) {
			sizeList[i] = rand() % 256;
		}

		begin = getCycleCount();

		for (uint32_t i = 0; i < iter; ++i) {

			p = malloc(sizeof(sizeList[i]));
			store[i] = p;
		}

		end = getCycleCount();

		for (uint32_t i = 0; i < iter; ++i) {
			free(store[i]);
		}
		final += (end - begin);
	}

	printf("-Average Cost: %d\n", final / (allRound * iter));

	return NULL;
}

int testmemorypool(int argc, char **argv) {

	pthread_t pid1, pid2, pid3, pid4, pid5, pid6;

	int32_t i1, i2, i3, i4, i5, i6;
	i1 = 1;
	i2 = 2;
	i3 = 3;
	i4 = 4;
	i5 = 5;
	i6 = 6;

	pthread_create(&pid1, NULL, memoryThread, &i1);
	pthread_create(&pid2, NULL, memoryThread, &i2);
	pthread_create(&pid3, NULL, memoryThread, &i3);
	pthread_create(&pid4, NULL, memoryThread, &i4);
	pthread_create(&pid5, NULL, memoryThread, &i5);
	pthread_create(&pid6, NULL, memoryThread, &i6);

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
	pthread_join(pid3, NULL);
	pthread_join(pid4, NULL);
	pthread_join(pid5, NULL);
	pthread_join(pid6, NULL);

	return 0;
}
TEST(testmemorypool);

