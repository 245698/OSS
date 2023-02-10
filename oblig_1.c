#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int nrOfGuesses;

/* P1 skal kun få reade på ene FD, mens P2 skal kun få write på ene FD, og motsatt */
/* Creating the file descriptor
   Read = [0], Write = [1] 
*/
int p_Read_c_Write[2]; // Parent read || Child write
int p_Write_c_Read[2];  // Parent write || Child read

int main(int argc, char *argv[]) {

/* Forking the process
   returns zero in the child process
   returns positive integer in the parent process (which is the child PID)
*/
int id = fork();

pipe(FDParent);
pipe(FDChild);

 // child process because return value is zero
    if (id == 0)
        printf("Hello from Child!\n");
  
    // parent process because return value is non-zero.
    else
        printf("Hello from Parent!\n");

}

