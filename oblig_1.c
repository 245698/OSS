#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>



/* P1 skal kun få reade på ene FD, mens P2 skal kun få write på ene FD, og motsatt */
/* Creating the file descriptor
   Read = [0], Write = [1] 
*/
int pipe_1[2]; // Parent read || Child write
int pipe_2[2];  // Child read  || Parent write
int nrOfGuesses;
int drawnNumber;

/* Function prototypes */
int drawRandomInteger();
bool forkSuccessful(int id);
bool isChildProcess(int id);
bool isParentProcess(int id);



int main(int argc, char *argv[]) {

    /* Forking the process
    returns zero in the child process.
    returns positive integer in the parent process (which is the child PID).
    returns negative integer if the fork process failed.
    */
    int id = fork();

    // checks if process is a child, return value is zero.
    if ( isChildProcess(id) ) { 
	
		printf("hello from child\n");
		drawnNumber = drawRandomInteger();
		printf("%d\n",drawnNumber);
		
		}
        
  
    // checks if process is a parent, return value is non-zero.
    else if ( isParentProcess(id) ){ printf("hello from parent\n"); }

}

/* Checks wether or not a fork was sucessful or not.
   Returns 0 (false) if input parameter is a negative integer.
   Returns 1 (true) if input parameter is a positive integer.
*/
bool forkSuccessful(int id) {

    if (id < 0) { printf("fork failed!\n"); return 0; }
    else { printf("fork is successful!\n"); return 1; }
    
}

/* Checks if a process is a child.
   Returns 1 (true) if id
*/
bool isChildProcess(int id) {

    if (id == 0) { return 1; }
    else { return 0; }

}
/* Checks if a process is a parent.
   Returns 1 (true) if id 
*/
bool isParentProcess(int id) {

    if (id >= 1) { return 1; }
    else { return 0; }

}


int drawRandomInteger() { 

	int randomnumber;
	srand ( time(NULL) ); //generates seed for rand() func
    randomnumber = rand() % 1000 + 1; //generates a random integer between 1 and 1000
    return randomnumber;
	
	}
  
  /*
    getpid(); //returns the process id of it's caller
	getppid(); //returns the process id of it's callers parent
    pipe(pipe_1); //
    pipe(pipe_2);
	
	*/
