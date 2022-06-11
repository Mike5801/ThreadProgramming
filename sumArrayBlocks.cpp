#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <iomanip>

const int threads = 8;
const int size_arr = 50000;

typedef struct {
	int start, end;
	int* arr;
} Block;

void* sumArr(void* args) {
	sleep(1);
	Block *block;
	int acum;
	block = (Block*)args;
	acum = 0;
	for (int i = block->start; i < block->end; i++) {
		acum += block->arr[i];
	}
	
	printf("Sum of block: %d | ", acum);
	printf("Block start: %d | ", block->start);
	printf("Block end: %d \n", block->end);
	*(int*)args = acum;
	return args;
}

int main(int argc, char* argv[]) {
	pthread_t th[threads];
	Block blocks[threads];
	int *a;
	int block_size, i, j;
	int totalSum, *acum;
	

	a = new int[size_arr];

	for (int i = 0; i < size_arr; i++) {
		a[i] = i + 1;
	}

	block_size = size_arr / threads;
	for (i = 0; i < threads; i++) {
		blocks[i].arr = a;
		blocks[i].start = i * block_size;
		blocks[i].end = i != (threads - 1) ? (i + 1) * block_size : size_arr;
	}

	for (i = 0; i < threads; i++) {
		if (pthread_create(&th[i], NULL, sumArr, (void*)&blocks[i])) {
			perror("Failed creating thread");
		}
	}

	totalSum = 0;
	for (i = 0; i < threads; i++) {
		if (pthread_join(th[i], (void**) &acum)) {
			perror("Failed to join thread");
		}
		//printf("Acum value: %d\n", (*acum));
		totalSum += *acum;
		delete acum;
	}

	printf("Total sum: %d\n", totalSum);
	
	return 0;
}