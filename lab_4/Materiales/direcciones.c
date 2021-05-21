#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char e1[0x100], e2[0x100];
char e3[] = "Hola mundo!";
char* m = "Hola mundo!";

void escribe(char* texto, void *dir) {
	printf("Dirección de %-4s = %p\n", texto, dir);
}

int main(void) {
	char* p1 = malloc(0x1000);
	char* p2 = malloc(0x1000);
  printf("\n");
	escribe("main", main);
	escribe("e1", &e1);
	escribe("e2", &e2);
  escribe("e3", &e3);
  escribe("e3[0]", &e3[0]);
	escribe("m", &m);
	escribe("m[0]", &m[0]);
	escribe("p1", &p1);
	escribe("p2", &p2);
	escribe("*p1", p1);
	escribe("*p2", p2);
	sleep(1000);
}
