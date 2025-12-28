// Q6: Using exec() system calls for odd/even series

// Main program: q6_main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process - execute even series program
        execl("./q6_even", "q6_even", argv[1], NULL);
        printf("exec failed for even series\n");
        return 1;
    }
    else {
        // Parent process - execute odd series program
        wait(NULL);  // Wait for child first
        execl("./q6_odd", "q6_odd", argv[1], NULL);
        printf("exec failed for odd series\n");
        return 1;
    }
    
    return 0;
}

// Compile: gcc -o q6_main q6_main.c
// Run: ./q6_main 10