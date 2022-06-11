#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

const int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

const int threads = 2;

void* routine(void* arg) {
	//sleep(1);
	int index = *(int*)arg;
	int sum = 0;
	for (int j = 0; j < 5; j++) {
		sum += primes[index + j];
	}
	*(int*)arg = sum;
	return arg;

}

int main(int argc, char* argv[]) {
	pthread_t th[threads];
	int i;
	for (i = 0; i < threads; i++) {
		int* a = (int*)malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, routine, a) != 0) {
			perror("Failed to create thread");
		}
	}

	int globalSum = 0;
	for (i = 0; i < threads; i++) {
		int* result;
		if (pthread_join(th[i], (void**) &result) != 0) {
			perror("Failed to join thread");
		}
		globalSum += *result;
		free(result);
	}
	printf("Global sum: %d\n", globalSum);
	return 0;
}