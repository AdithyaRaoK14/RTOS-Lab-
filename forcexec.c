#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    
    printf("=== PARENT PROCESS ===\n");
    printf("Parent PID: %d\n", getpid());
    printf("Parent PPID: %d\n", getppid());
    printf("I'm the parent\n\n");
    
    // Fork a child process
    pid = fork();
    
    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // CHILD PROCESS
        printf("=== CHILD PROCESS ===\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());
        printf("I'm the child\n\n");
        
        // OPTION 1: Execute a command (like ls, pwd, date)
        // Uncomment one of these based on question:
        
        // execlp("ls", "ls", NULL);              // For simple ls
        // execlp("ls", "ls", "-l", NULL);        // For ls -l
        // execlp("pwd", "pwd", NULL);            // For pwd
        // execlp("date", "date", NULL);          // For date
        
        // OPTION 2: Do some computation (Fibonacci, odd/even series)
        printf("Child doing computation:\n");
        int n = 10; // Change based on requirement
        if (argc > 1) {
            n = atoi(argv[1]); // Get from command line
        }
        
        // Fibonacci example
        int a = 1, b = 1, next;
        printf("Fibonacci: %d %d ", a, b);
        for (int i = 2; i < n; i++) {
            next = a + b;
            printf("%d ", next);
            a = b;
            b = next;
        }
        printf("\n");
        
        exit(0);
    }
    else {
        // PARENT PROCESS
        printf("Parent waiting for child (PID: %d)...\n", pid);
        
        // IMPORTANT: Uncomment this to use wait()
        wait(NULL);  // Comment this line to see difference without wait
        
        printf("Parent: Child has finished\n");
        
        // Parent can also do work (odd series example)
        printf("\nParent generating odd series:\n");
        int n = 10;
        if (argc > 1) {
            n = atoi(argv[1]);
        }
        for (int i = 0; i < n; i++) {
            printf("%d ", 2*i + 1);
        }
        printf("\n");
    }
    
    return 0;
}

/*
COMPILATION: gcc program.c -o program
EXECUTION: ./program
WITH ARGUMENT: ./program 15

KEY POINTS TO REMEMBER:
1. fork() returns 0 in child, child's PID in parent, -1 on error
2. getpid() = current process ID
3. getppid() = parent process ID
4. wait(NULL) makes parent wait for child to finish
5. exec family replaces current process with new program
*/