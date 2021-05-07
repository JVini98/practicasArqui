#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 5
#define NUM_CLIENTS 20
#define SLEEP 300

long sillones[BUFFER_SIZE];
int contador_clientes = 0;

sem_t *mutex, *clientes;



void *peluquero(void *args){

	long id;

	while(1){
		sem_wait(clientes);

		sem_wait(mutex);
		id = sillones[0];
		printf("I am costumer %ld... Moving from the Coach to the free chair\n", id);
		for(int i = 1; i<BUFFER_SIZE ; i++){
			sillones[i-1] = sillones[i] ;
		}
		contador_clientes--;
		sem_post(mutex);

		printf("Shz! Shz! I am Barber Patrick and I am cutting hair! Shz! Shz!\n\n");
		printf("I am costumer %ld... Enjoying a nice haircut\n", id);
		sleep(3);

		printf("I am Barber Patrick and I am done\n");
		printf("I am costumer %ld... Exiting the barbershop\n", id);

	}

	return NULL;
}

void  *cliente(void *args){

	long id = (long) args;
	
	sem_wait(mutex);
	
	if(contador_clientes == 5){
		printf("I am costumer %ld... Oooohhhh Noooo! The barbershop is full!\n", id);
	}else{
		
			printf("I am costumer %ld... Resting at the couch\n", id);
			sillones[contador_clientes] = id;
			contador_clientes++;
			sem_post(clientes);
		
	}

	sem_post(mutex);
	
	return NULL;
}

int main(){
	srandom(time(NULL));

	pthread_t tclientes[NUM_CLIENTS], tpeluquero;
	mutex = sem_open("/mutex", O_CREAT, 0644, 1);
	clientes = sem_open("/clientes", O_CREAT, 0644, 0);

	pthread_create(&tpeluquero, NULL, peluquero, NULL);

	for(long i = 0; i<NUM_CLIENTS; i++){
		pthread_create(&tclientes[i], NULL, cliente,(void*) i);
		sleep((random() % 3));
	} 


	for (int i = 0; i < NUM_CLIENTS; i++) {
    	pthread_join(tclientes[i], NULL);
  	}
  	pthread_join(tpeluquero, NULL);
	sem_close(mutex);
	sem_close(clientes);
	exit(0);
}