#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/* Creating the file descriptor
   First pipe sends from parent
   Second pipe sends from child
*/
//parent write, child read
int fileDescriptor_1[2]; //Read = [0], Write = [1]
//child write, parent read
int fileDescriptor_2[2]; //Read = [0], Write = [1] 
int nrOfGuesses;
int drawnNumber;
int guessedNumber;
int parentAnswer;
int childAnswer;
int childPromt;
pid_t processID;


/* Function prototypes */
int drawRandomInteger();


int main(int argc, char *argv[]) {

    
	/* Creating the pipes and checks for errors */
	if ( pipe(fileDescriptor_1) == -1 ) { printf("Pipe Failed!\n"); return 1; }
	if ( pipe(fileDescriptor_2) == -1 ) { printf("Pipe Failed!\n"); return 1; }
	
	/* Forking the process
    returns zero in the child process.
    returns positive integer in the parent process (which is the child PID).
    returns negative integer if the fork process failed.
    */
    processID = fork();
	
	/* Checks if fork was successful */
	if (processID < 0) { printf("Fork Failed!"); return 1; }
    
	// Child process
    if ( processID == 0 ) { 
		
		close(fileDescriptor_1[1]); //close write end of first pipe
		printf("hello from child\n");
		drawnNumber = drawRandomInteger();
		printf("%d\n",drawnNumber);
		
		//read guess from parent
		read(fileDescriptor_1[0], &parentAnswer, sizeof(parentAnswer));
		
		if (parentAnswer > drawnNumber) { childPromt = -1; }
		else if (parentAnswer < drawnNumber) { childPromt = 1; }
		else { childPromt = 0; }
		
		write(fileDescriptor_2[1], &childPromt, sizeof(childPromt));
		
		// Wait for parent to send an answer
        wait(NULL);
		
		
	}
        
    // Parent process
    if ( processID > 0 ) { 
	
		close(fileDescriptor_2[1]); //close write end of second pipe
		printf("hello from parent\n");
		guessedNumber = 500;
		
		//write guessedNumber
		write (fileDescriptor_1[1], &guessedNumber, sizeof(guessedNumber));
		
		// Wait for child to send an answer
        wait(NULL);
		
		// Read answer from child
		read(fileDescriptor_2[0], &childAnswer, sizeof(childAnswer));
		
		if (childAnswer == -1) { printf("guess was too high!\n"); guessedNumber--; }
		else if (childAnswer == 1) { printf("guess was too low!\n"); guessedNumber++; }
		else { printf("guess was too correct!\n"); }
		
		}	
}

/* Functions */
int drawRandomInteger() { 

	int randomnumber;
	srand ( time(NULL) ); //generates seed for rand() func
    randomnumber = rand() % 1000 + 1; //generates a random integer between 1 and 1000
    return randomnumber;
	
	}