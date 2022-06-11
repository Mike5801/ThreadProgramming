#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine(void* arg) {
	for (int i = 0; i < 10000000; i++) {
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// Read mails
		// Increment the value
		// Write mails back to memory

		/*
		When the threads starts running the program and
		then after some time thread 2 stops while thread 1
		keeps running, then at some point, when thread 2 starts
		again, then the value gets restarted where thread 2
		stopped.
		*/
	}
}

int main(int argc, char* argv[]) {
	pthread_t th[8];
	int i;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 8; i++) {
		if (pthread_create(&th[i], NULL, routine, NULL) != 0) {
			perror("Failed to create thread");
			return 1;
		}
		printf("Thread %d has started \n", i);
	}
	for (i = 0; i < 8; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			return 2;
		}
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}