// Q8: Two children - one converts lowercase to uppercase, other counts 'a'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    pid_t pid1, pid2;
    FILE *file, *outfile;
    char ch;
    int count_a = 0;
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // First child - convert lowercase to uppercase
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
        
        outfile = fopen("output_uppercase.txt", "w");
        if (outfile == NULL) {
            printf("Child 1: Cannot create output file\n");
            fclose(file);
            return 1;
        }
        
        while ((ch = fgetc(file)) != EOF) {
            if (islower(ch)) {
                fputc(toupper(ch), outfile);
            } else {
                fputc(ch, outfile);
            }
        }
        
        fclose(file);
        fclose(outfile);
        printf("Child 1 (PID: %d) - Converted to uppercase, saved in output_uppercase.txt\n", getpid());
        return 0;
    }
    
    // Second child - count 'a' characters
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
            if (ch == 'a' || ch == 'A') {
                count_a++;
            }
        }
        
        fclose(file);
        printf("Child 2 (PID: %d) - Total 'a' characters: %d\n", getpid(), count_a);
        return 0;
    }
    
    // Parent waits for both children
    wait(NULL);
    wait(NULL);
    printf("Parent (PID: %d) - Both children completed\n", getpid());
    
    return 0;
}

// Compile: gcc -o q8 q8.c
// Run: ./q8 testfile.txt