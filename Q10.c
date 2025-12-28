// Q10: Fork a process and execute ls command using execlp
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    printf("Parent Process (PID: %d) - Forking...\n", getpid());
    
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child Process (PID: %d) - Executing ls command:\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        
        // If execlp fails
        printf("execlp failed\n");
        return 1;
    }
    else {
        // Parent process
        wait(NULL);
        printf("Parent Process (PID: %d) - Child completed\n", getpid());
    }
    
    return 0;
}

// Compile: gcc -o q10 q10.c
// Run: ./q10