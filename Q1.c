// Q1: Demonstrate fork() system call with parent and child displaying pid, ppid
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("I'm the child\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());
    }
    else {
        // Parent process
        printf("I'm the parent\n");
        printf("Parent PID: %d\n", getpid());
        printf("Parent PPID: %d\n", getppid());
    }
    
    return 0;
}