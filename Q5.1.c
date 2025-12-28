// Q5(i): Parent generates odd series, child generates even series
// Using command line argument
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int n, i;
    
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }
    
    n = atoi(argv[1]);
    
    if (n <= 0) {
        printf("Please enter a positive number\n");
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process - generate even series
        printf("Child Process (PID: %d) - Even Series:\n", getpid());
        for (i = 0; i < n; i++) {
            printf("%d ", 2 * i);
        }
        printf("\n");
    }
    else {
        // Parent process - generate odd series
        printf("Parent Process (PID: %d) - Odd Series:\n", getpid());
        for (i = 0; i < n; i++) {
            printf("%d ", 2 * i + 1);
        }
        printf("\n");
        wait(NULL);
    }
    
    return 0;
}

// Compile: gcc -o q5a q5a.c
// Run: ./q5a 10