#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* roll_dice(void* arg) {
	int value = (rand() % 6) + 1;
	int* result = (int*) malloc(sizeof(int));
	*result = value;
	//printf("%d\n", value);
	return (void*) result;
}

int main(int argc, char* argv[]) {
	const int threads = 8;
	int* res;
	int i;
	srand(time(NULL));
	pthread_t th[threads];

	for (i = 0; i < threads; i++) {
		if (pthread_create(&th[i], NULL, roll_dice, NULL) != 0) {
			return 1;
		};
	}
	for (i = 0; i < threads; i++) {
		if (pthread_join(th[i], (void**)&res) != 0) {
			return 2;
		}
		printf("Result: %d\n", *res);
	}
	
	free(res);
	return 0;
}