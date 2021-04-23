#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
  int fd[2];
  pid_t childpid;
  // Creamos el pipe, el array fd se usa para devolver 2 descriptores de fichero
  // que hacen referencia al principio y final del pipe
  pipe(fd);

  if ((childpid = fork()) == 0) {
    // El hijo va a ser ls
    // dup2 crea una copia del fichero apuntado por fd[1] usando el descriptor
    // de fichero STDOUT_FILENO. Es decir, tras dup2, la salida estándar de este
    // proceso coincidirá con la salida del pipe y los dos pueden usarse
    // independientemente
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]); // ls no va a usar la entrada del pipe
    close(fd[1]); // ls va a usar como salida STDOUT_FILENO, que es una copia de fd[1]. Podemos cerrar esta copia
    execl("/bin/ls", "ls", "-l", NULL);
    perror("Fallo en ls");
  } else {
    // hacemos que la entrada estándar sea una copia del extremo de lectura del pipe
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]); // cerramos fd[0], ya que ya hemos mapeado este extremo del pipe a STDIN
    close(fd[1]); // sort no va a hacer uso del extremo de escritura
    execl("/usr/bin/sort", "sort", "-k9", NULL);
    perror("Fallo en sort");
  }
  exit(0);
}
