#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void hijo(int sig) {
	printf("\t\t¡Padre! ¿Qué haces?\n");
	printf("\t\tFinal de ejecución de %d \n", getpid());
	kill(getppid(), SIGUSR1);
	exit(0);
}

void padre(int sig) {
	printf("\t¡Hijo! ¿Qué he hecho?\n");
	printf("\tFinal de ejecución de %d \n", getpid());
	exit(0);
}

int main(void) {
	long long int i;
	pid_t rf;
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
			sleep(1);	//suspende el proceso 1 segundo.
			printf("\tVoy a matar a mi hijo.\n");
			sleep(15);	//suspende el proceso 15 segundos.
			kill(rf, SIGUSR1);
			sleep(1);
	}
	exit(0);
}
