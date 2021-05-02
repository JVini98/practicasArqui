#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_message(char* message) {
    write(1,message,sizeof(message));
}

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
    exit(0);
  }
}
