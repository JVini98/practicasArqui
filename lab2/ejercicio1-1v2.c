#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*

             1
       2             3
    4    6      5       7
  8 10 12 14  9  11  13  15
*/
void show_message(char* message) {
    printf("<%s>\n", message);
}

string  identificar(int id){

  switch (id) {
    case 1:
      return "A";
    case 2:
      return "AA";
    case 3:
      return "AB";
    case 4:
      return "AAA";
    case 5:
      return "AAB";
    case 6:
      return "ABA";
    case 7:
      return "ABB";

  }

}

int bifurcar(int idPadre){

  pid_t rf = fork();

  switch (rf) {
    case -1:
      printf("\nNo he podido crear el proceso hijo");
      break;
    case 0:
      return idPadre + 1;
    default:
      show_message(identificar(idPadre));
      kill():
  }
}


int main(){

  int profundidad = 3;
  idPadre = 1

  for(int i = 0; i<profundidad; i++){
      bifurcar();
  }


}
