// Q13: Child generates Fibonacci with error checking for non-negative numbers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int n, i;
    int a = 1, b = 1, next;
    
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        printf("Please provide a non-negative number\n");
        return 1;
    }
    
    n = atoi(argv[1]);
    
    // Error checking for non-negative number
    if (n < 0) {
        printf("Error: Please enter a non-negative number (n >= 0)\n");
        return 1;
    }
    
    if (n == 0) {
        printf("No Fibonacci numbers to display\n");
        return 0;
    }
    
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process - generate Fibonacci series
        printf("Child Process (PID: %d)\n", getpid());
        printf("Fibonacci Series (first %d numbers):\n", n);
        
        if (n >= 1) printf("%d ", a);
        if (n >= 2) printf("%d ", b);
        
        for (i = 3; i <= n; i++) {
            next = a + b;
            printf("%d ", next);
            a = b;
            b = next;
        }
        printf("\n");
        
        printf("Child process completed successfully\n");
    }
    else {
        // Parent process
        int status;
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("\nParent Process (PID: %d)\n", getpid());
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    }
    
    return 0;
}

// Compile: gcc -o q13 q13.c
// Run: ./q13 10
// Test error: ./q13 -5