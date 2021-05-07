#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

char mensaje[100]; // para evitar warning de devolver vaiable local

char * crear_mensaje(){

    printf("\nEscribe un mensaje para mi hijo: ");
    fgets(mensaje, sizeof(mensaje), stdin);
    return mensaje;
}


int main(void) {
    int fd[2];
    pid_t pid;
    // Creamos el pipe, el array fd se usa para devolver 2 descriptores de fichero que hacen referencia al principio y final del pipe
    pipe(fd);

    pid = fork();

    switch (pid) {
        case -1: {
            printf("ERROR, no se ha podido crear el proceso");
            exit(0);
        }

        case 0: { // es hijo. Debe esperar a recibir señal de que el mensaje del padre está listo

            wait(NULL);
            char leido[sizeof(mensaje)];

            close(fd[1]); // cerramos el lado de escritura del pipe
            read(fd[0], &leido, sizeof(mensaje));
            printf("\nMi padre dice: %s", leido);
            close(fd[0]);


            break;

        }

            while (strcmp(mensaje, "FIN\n") != 0) {

                default: { // padre escribe el mensaje. El hijo mientras debe esperar al mensaje -> wait(NULL) -> incluir librerias

                    char *enviado = crear_mensaje(); //puntero a mensaje

                    close(fd[0]); //cerramos el lado de lectura del pipe
                    write(fd[1], enviado, sizeof(enviado));
                    close(fd[1]);

                }
                wait(NULL);
            }

    }
}