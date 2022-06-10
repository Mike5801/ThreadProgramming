#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;

void* routine(void* arg) {
	for (int i = 0; i < 1000000; i++) {
		mails++;
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
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, routine, NULL) != 0) {
		return 1;
	};
	if (pthread_create(&t2, NULL, routine, NULL) != 0) {
		return 2;
	};
	if (pthread_join(t1, NULL) != 0) {
		return 3;
	};
	if (pthread_join(t2, NULL) != 0) {
		return 4;
	};
	printf("Number of mails: %d\n", mails);
	return 0;
}