#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void yeah() {
 printf("Soy un hacker!\n");
}

int main(int argc, char **argv) {
 int (*fp)();
 char buffer[8];

 fp = 0;

 // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 // !NUNCA SE DEBE USAR LA FUNCION gets!
 // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 gets(buffer);
 if(fp) {
  printf("LLamada al puntero a función, saltando a %p\n", fp);
  fp();
 }
}
