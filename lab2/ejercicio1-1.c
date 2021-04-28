#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void show_message(char* message) {
    printf("<%s>\n", message);
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t aa, ab, aaa, aab, aba, abb;

    show_message("A");
    aa = fork();
    switch (aa) {
        case -1:
            printf("No he podido crear el proceso hijo \n");
            break;
        case 0:

              show_message("AA");
              aaa = fork();
              switch (aaa) {
                case -1:
                  printf("No he podido crear el proceso aaa \n");
                  break;
                case 0:
                  show_message("AAA");
                  break;
                default:
                  aab = fork();
                  switch (aab) {
                    case 0:
                      show_message("AAB");
                      break;
                  }

              }
            break;
        default:

            ab = fork();

            switch (ab) {
              case 0:
                  show_message("AB");
                  aba = fork();

                  switch (aba) {
                    case 0:
                      show_message("ABA");
                      break;
                    case -1:
                      printf("No he podido crear el proceso aaa \n");
                      break;
                    default:
                      abb = fork();
                      switch (abb) {
                        case 0:
                          show_message("ABB");
                          break;
                      }
                  }
                  break;
              case -1:
                  printf("No he podido crear el proceso hijo \n");
                  break;
            }

            /*switch (ab) {
              case -1:
                  printf("No he podido crear el proceso hijo \n");
                  break;
              default:
                  show_message("ABB");
                  abb = fork();*/
            //sleep(30); //suspende el proceso 30 segundos. Acaba antes el hijo.
    //printf("Final de ejecución de %d \n", getpid());
    exit(0);
  }
}
