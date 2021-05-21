#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE_SOFA 5
#define BUFFER_SIZE_BAR 15
#define NUM_CLIENTS 50
#define SLEEP 300

long sillones[BUFFER_SIZE_SOFA];
long bar[BUFFER_SIZE_BAR];
int contador_clientes_sofa = 0;
int contador_clientes_bar = 0;

sem_t *mutex, *clientes;



void *peluquero(void *args){

	long id;

	while(1){
		sem_wait(clientes);

		sem_wait(mutex);

		id = sillones[0];
		printf("I am costumer %ld... Moving from the Coach to the free chair\n", id);
		
		for(int i = 1; i<BUFFER_SIZE_SOFA ; i++){
			sillones[i-1] = sillones[i] ;
		}

		if(contador_clientes_bar != 0){

			sillones[BUFFER_SIZE_SOFA-1] = bar[0];
			printf("I am costumer %ld... Moving from the Bar to the Coach\n", bar[0]);

			for(int i = 1; i<BUFFER_SIZE_BAR ; i++){
				bar[i-1] = bar[i];
			}
			
			contador_clientes_bar--;	
		}else{
			contador_clientes_sofa--;
		}

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
	
	if(contador_clientes_sofa == BUFFER_SIZE_SOFA){
		if(contador_clientes_bar == BUFFER_SIZE_BAR){
			printf("I am costumer %ld... Oooohhhh Noooo! The barbershop is full!\n", id);
		} else {
			printf("I am costumer %ld... Having a drink at the bar\n", id);
			bar[contador_clientes_bar] = id;
			contador_clientes_bar++;
			sem_post(clientes);
		}	
	}else{
		
			printf("I am costumer %ld... Resting at the couch\n", id);
			sillones[contador_clientes_sofa] = id;
			contador_clientes_sofa++;
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
		sleep((random() % 2));
	} 


	for (int i = 0; i < NUM_CLIENTS; i++) {
    	pthread_join(tclientes[i], NULL);
  	}
  	pthread_join(tpeluquero, NULL);
	sem_close(mutex);
	sem_close(clientes);
	exit(0);
}