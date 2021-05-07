#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *archivo_copia;

void crear_fork(char* archivo){
    pid_t pid;
    pid = fork();

    switch (pid) {
        case -1:
            printf("ERROR. El archivo no pudo ser guardado\n");
            break;

        case 0:

            archivo_copia = strdup(archivo);

            for (int i = 0; i < strlen(archivo_copia); i++) {

                if (archivo_copia[i] == '.') {

                    archivo_copia[i] = '\0';
                }
            }

            strcat(archivo_copia, ".bak");

            char * const ls_command[] = {"cp", archivo, archivo_copia, NULL};
            execvp(ls_command[0], ls_command);

            break;

        default:
            wait(NULL);

    }

}

int main(int argc, char* argv[]) {

    for (int n = 1; n < argc; n++) {

        crear_fork(argv[n]);
    }

}
