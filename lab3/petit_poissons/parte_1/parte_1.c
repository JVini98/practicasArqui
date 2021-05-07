#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_CLIENTS 20
#define SLEEP 300

int sillones[BUFFER_SIZE];
int contador_clientes = 0;

void *peluquero(void *args){

	return NULL;
}

void  *cliente(void *args){

	long show = (long) args;
	

	if(contador_clientes == 5){
		printf("I am costumer %ld... Oooohhhh Noooo! The barbershop is full!", show);
	}else{
		contador_clientes++;
		printf("I am costumer %ld... Resting at the couch", show);
	}
	
	return NULL;
}

int main(){
	srandom(time(NULL));

	pthread_t tclientes[NUM_CLIENTS], tpeluquero;

	for(long i = 0; i<NUM_CLIENTS; i++){
		pthread_create(&tclientes[i], NULL, cliente,(void*) i);
		sleep((random() % 3) + 1);
	} 
}