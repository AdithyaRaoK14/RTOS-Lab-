// Q7: Two children - one counts lines, other counts characters
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid1, pid2;
    FILE *file;
    char ch;
    int lines = 0, chars = 0;
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // First child - count lines
    pid1 = fork();
    
    if (pid1 < 0) {
        printf("Fork 1 failed\n");
        return 1;
    }
    else if (pid1 == 0) {
        // First child process
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Child 1: Cannot open file %s\n", argv[1]);
            return 1;
        }
        
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '\n') {
                lines++;
            }
        }
        
        fclose(file);
        printf("Child 1 (PID: %d) - Total lines: %d\n", getpid(), lines);
        return 0;
    }
    
    // Second child - count characters
    pid2 = fork();
    
    if (pid2 < 0) {
        printf("Fork 2 failed\n");
        return 1;
    }
    else if (pid2 == 0) {
        // Second child process
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Child 2: Cannot open file %s\n", argv[1]);
            return 1;
        }
        
        while ((ch = fgetc(file)) != EOF) {
            chars++;
        }
        
        fclose(file);
        printf("Child 2 (PID: %d) - Total characters: %d\n", getpid(), chars);
        return 0;
    }
    
    // Parent waits for both children
    wait(NULL);
    wait(NULL);
    printf("Parent (PID: %d) - Both children completed\n", getpid());
    
    return 0;
}

// Compile: gcc -o q7 q7.c
// Run: ./q7 testfile.txt