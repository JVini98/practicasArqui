//seccion 7-- el comando que se ha usado es kill -SIGUSR2
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

pid_t rf;//vbl global para poder acabar con el hijo desde dios()

void hijo(int sig) {
	printf("\t\t¡Padre! ¿Qué haces?\n");
	printf("\t\tFinal de ejecución de %d \n", getpid());
	kill(getppid(), SIGUSR1); //hijo "mata" padre
	exit(0);
}

void padre(int sig) {
	printf("\t¡Hijo! ¿Qué he hecho?\n");
	printf("\tFinal de ejecución de %d \n", getpid());
	exit(0);
}

void dios(int sig){ 
	printf("\t\t¡El Señor ha intervenido!, ¡se ha interrumpido el sacrificio!\n");
	kill(rf,SIGUSR2);
	exit(0);
}

int main(void) {
	rf = fork();
	switch (rf) {
		case -1:
			printf("No he podido crear el proceso hijo. \n");
			break;
		case 0:
			printf("\t\tSoy Isaac, mi PID es %d y mi PPID es %d. \n", getpid(), getppid());
			signal(SIGUSR1, hijo);
			pause(); // wait until signal
			break;
		default:
			printf("\tSoy Abraham, mi PID es %d y el PID de mi hijo es %d. \n", getpid(), rf);
			signal(SIGUSR1, padre);
			sleep(1);
			printf("\tVoy a matar a mi hijo.\n");
			signal(SIGUSR2,exit);//Si recibe SIGUSR2, acaba el proceso y llama a dios()
			signal(SIGUSR2, dios);
			sleep(15);	//suspende el proceso 15 segundos.
			kill(rf, SIGUSR1);
			sleep(1);
	}
	exit(0);
}
