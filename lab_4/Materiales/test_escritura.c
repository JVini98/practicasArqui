#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

char dato;
char* dir;


int main(int argc, char *argv[]) {
    sleep(10);
	if (argc != 2) {
		fprintf(stderr, "%s: se necesita una direccion\n", argv[0]);
		exit(1);
	}
    // obtenemos la dirección de memoria en donde intentaremos
    // escribir de los argumentos de línea de comandos.
	dir  = (char*)strtoul(argv[1], NULL, 0);
	printf ("Probando a escribir en la dirección virtual %p: ", dir);
    fflush(stdout);
	*dir = dato;
    // Si llegamos hasta aquí, no ha habido fallos y tenemos permisos de acceso
	printf("escribible\n");
	sleep(1);
	exit(0);
}
