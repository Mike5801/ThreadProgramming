#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
const int threads = 6;
int fuel = 0;

void* fuel_filling(void* args) {
	for (int i = 0; i < 5; i++) {
		pthread_mutex_lock(&mutexFuel);
		fuel += 30;
		printf("Filled fuel: %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
		pthread_cond_broadcast(&condFuel);
		sleep(1);
	}

}

void* car(void* args) {
	pthread_mutex_lock(&mutexFuel);
	while (fuel < 40) {
		printf("No fuel. Waiting...\n");
		pthread_cond_wait(&condFuel, &mutexFuel);

		// Equivalent to:
		// pthread_mutex_unlock(&mutexFuel);
		// wait for signal on condFuel
		// pthread_mutex_lock(&mutexFuel);

	}
	fuel -= 40;
	printf("Got fuel. Now left: %d\n", fuel);
	pthread_mutex_unlock(&mutexFuel);
	//printf("Here to get fuel\n");
}

int main(int argc, char* argv[]) {
	pthread_t th[threads];
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);

	int i;
	for (i = 0; i < threads; i++) {
		if (i == 4 || i == 5) {
			if (pthread_create(&th[i], NULL, fuel_filling, NULL) != 0) {
				perror("Failed to create thread");
			}
		}
		else {
			if (pthread_create(&th[i], NULL, car, NULL) != 0) {
				perror("Failed to create thread");
			}
		}
	}

	for (i = 0; i < threads; i++) {
		if (pthread_join(th[i], NULL)) {
			perror("Failed to join thread");
		}
	}
	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);
	return 0;
}
