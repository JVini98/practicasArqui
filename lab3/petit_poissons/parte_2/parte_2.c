#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define THREAD_NUM 2

sem_t *mutexBuffer;

int buffer[5];
int count = 0;

void* producer(void* args) {
	while(1){
		int x = rand() % 5;

		sem_wait(mutexBuffer);

		if(count < 5) {
			buffer[count] = x;
			count++;
		}

		sem_post(mutexBuffer);
	}
}

void* consumer(void* args) {
	while(1){
		sem_wait(mutexBuffer);
		if(count > 0){
			int y = buffer[count - 1];
			count--;
			printf("%d \n", y);
		}
		sem_post(mutexBuffer);
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	pthread_t th[THREAD_NUM];

	mutexBuffer = sem_open("/mutexBuffer", O_CREAT, 0644, 1);

	int i;
	for (int i = 0; i < THREAD_NUM; ++i){
		if (i % 2 == 0){
			if (pthread_create(&th[i], NULL, &producer, NULL) != 0){
				perror("Failed to create thread");
			}
		} else {
			if (pthread_create(&th[i], NULL, &consumer, NULL) != 0){
				perror("Failed to create thread");
			}
		}
	}

	for (i = 0; i < THREAD_NUM; i++){
		if (pthread_join(th[i],NULL) != 0) {
			perror("Failed to join thread");
		}
	}

	sem_close(mutexBuffer);

	return 0;
}