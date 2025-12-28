// Q15: Main program - Fork and execute child program
// This program forks a child and makes it execute a separate program

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    
    printf("Parent Process (PID: %d) - Starting...\n", getpid());
    
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process - execute the child program
        printf("Child Process (PID: %d) - Executing child program...\n\n", getpid());
        
        // Execute the compiled child program
        // You can choose any of the following child programs:
        execl("./q15_child_matrix", "q15_child_matrix", NULL);
        // OR: execl("./q15_child_string", "q15_child_string", NULL);
        // OR: execl("./q15_child_digits", "q15_child_digits", NULL);
        
        // If exec fails
        printf("exec failed - make sure to compile the child program first\n");
        return 1;
    }
    else {
        // Parent process
        printf("Parent Process - Waiting for child to complete...\n\n");
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("\nParent Process - Child completed with status: %d\n", WEXITSTATUS(status));
        }
    }
    
    return 0;
}

// Compilation steps:
// 1. First compile the child program: gcc -o q15_child_matrix q15_child_matrix.c
// 2. Then compile this main program: gcc -o q15_main q15_main.c
// 3. Run: ./q15_main