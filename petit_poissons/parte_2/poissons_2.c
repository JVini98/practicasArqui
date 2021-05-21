#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAX_CLIENTS 100
#define MAX_SOFAS 5
#define MAX_BAR 15
#define PASS_SLEEP 4

sem_t sem_sofa, sem_patrick, sem_chair_client, sem_chair_space, sem_sofa_space_2;
pthread_mutex_t mutex;
int sofa_space = MAX_SOFAS, bar_space = MAX_BAR;

void* client() { // Hecho de maravilla
	pthread_mutex_lock(&mutex);
	if(bar_space == 0) {
	    printf("I'm costumer[%ld]: There is no free space neither at the bar or the coaches, sayonara baby!\n", pthread_self());
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	} else {
		bar_space--;
		pthread_mutex_unlock(&mutex);
	}
	printf("I'm costumer[%ld]: Enjoying a drink in the bar!\n", pthread_self());
	//Se limitan el numero de personas que ejecutan lo del espacio de lo sofas.
	sem_wait(&sem_sofa_space_2);
	//Inicia el sofa (persona se sienta en el)
	printf("I'm costumer[%ld]: I have finished my drink and I'm heading to the coach!\n", pthread_self());
	sem_post(&sem_sofa);
	pthread_exit(NULL);
}


void* sofa() {
	for(int n = 0; n < MAX_CLIENTS; n++) {
		sem_wait(&sem_sofa);

		pthread_mutex_lock(&mutex);
		bar_space ++;
		pthread_mutex_unlock(&mutex);

		printf("I'm costumer[%ld]: Resting at the coach!\n", pthread_self());
		// Block the chair so no one sits there
		sem_wait(&sem_chair_space);
		printf("I'm costumer[%ld]: Heading from sofa to the chair!\n", pthread_self());
		sem_post(&sem_sofa_space_2);

		//Arrance la conversación con patrick en la silla
		sem_post(&sem_chair_client);
	}
	pthread_exit(NULL);
}

void* patrick() {
	for(int n = 0; n < MAX_CLIENTS; n++) {
		//Patrick se duerme esperando
		sem_wait(&sem_patrick);
		printf("Shz! Shz! I am Barber Patrick and I'm cutting hair! Shz! Shz!\n");
		sem_post(&sem_chair_client);
		sem_wait(&sem_patrick);
		//Cortar pelo
		sleep(5);
		printf("I'm Barber Patrick and I'm done\n");
		sem_post(&sem_chair_client);
	}
	pthread_exit(NULL);
}

void* chair() {
	for(int n = 0; n < MAX_CLIENTS; n++) {
		// Pide a Patrick que despierte
		sem_wait(&sem_chair_client);
		sem_post(&sem_patrick);
		// sem_client --> bloquea al cliente que esta en la silla para que le corten el pelo
		sem_wait(&sem_chair_client);
		printf("I'm costumer[%ld]: Enjoying a nice haircut!\n", pthread_self());
		sem_post(&sem_patrick);
		sem_wait(&sem_chair_client);
		printf("I'm costumer[%ld]: Exiting the barbershop!\n", pthread_self());
		sem_post(&sem_chair_space);
	}
	pthread_exit(NULL);
}


int main() {

	pthread_t clients_th[MAX_CLIENTS];
	pthread_t sofas_th[MAX_SOFAS];
	pthread_t patrick_th, chair_th;

	pthread_mutex_init(&mutex, NULL);
	sem_init(&sem_sofa, 0, 0);
	sem_init(&sem_chair_client, 0, 0);
	sem_init(&sem_chair_space, 0, 1);
	sem_init(&sem_patrick, 0, 0);
	sem_init(&sem_sofa_space_2, 0, 5);

	pthread_create(&patrick_th, NULL, patrick, NULL);
	pthread_create(&chair_th, NULL, chair, NULL);
	for(int n = 0; n < MAX_SOFAS; n++) {
		pthread_create(&sofas_th[n], NULL, sofa, NULL);
	}
	for(int n = 0; n < MAX_CLIENTS; n++) {
		sleep((random()) % PASS_SLEEP);
		pthread_create(&clients_th[n], NULL, client, NULL);
	}

	pthread_join(patrick_th, NULL);
	pthread_join(chair_th, NULL);
	for(int n = 0; n < MAX_SOFAS; n++) {
		pthread_join(sofas_th[n], NULL);
	}
	for(int n = 0; n < MAX_CLIENTS; n++) {
		pthread_join(clients_th[n], NULL);
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&sem_sofa);
	sem_destroy(&sem_chair_client);
	sem_destroy(&sem_chair_space);
	sem_destroy(&sem_sofa_space_2);
	sem_destroy(&sem_patrick);

	exit(0);
}

