// Q4: Child generates Fibonacci series up to n numbers (command line argument)
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
        // Child process - generate Fibonacci series
        printf("Child Process (PID: %d) - Fibonacci Series:\n", getpid());
        
        if (n >= 1) printf("%d ", a);
        if (n >= 2) printf("%d ", b);
        
        for (i = 3; i <= n; i++) {
            next = a + b;
            printf("%d ", next);
            a = b;
            b = next;
        }
        printf("\n");
    }
    else {
        // Parent process
        wait(NULL);
        printf("Parent Process (PID: %d) - Child completed\n", getpid());
    }
    
    return 0;
}

// Compile: gcc -o q4 q4.c
// Run: ./q4 10