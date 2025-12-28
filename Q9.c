// Q9: Two children - one counts words, other inverts case
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    pid_t pid1, pid2;
    FILE *file, *outfile;
    char ch, prev = ' ';
    int word_count = 0;
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // First child - count words
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
            if ((ch == ' ' || ch == '\n' || ch == '\t') && 
                (prev != ' ' && prev != '\n' && prev != '\t')) {
                word_count++;
            }
            prev = ch;
        }
        
        // Count last word if file doesn't end with whitespace
        if (prev != ' ' && prev != '\n' && prev != '\t' && prev != EOF) {
            word_count++;
        }
        
        fclose(file);
        printf("Child 1 (PID: %d) - Total words: %d\n", getpid(), word_count);
        return 0;
    }
    
    // Second child - invert case
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
        
        outfile = fopen("output_inverted.txt", "w");
        if (outfile == NULL) {
            printf("Child 2: Cannot create output file\n");
            fclose(file);
            return 1;
        }
        
        while ((ch = fgetc(file)) != EOF) {
            if (islower(ch)) {
                fputc(toupper(ch), outfile);
            } else if (isupper(ch)) {
                fputc(tolower(ch), outfile);
            } else {
                fputc(ch, outfile);
            }
        }
        
        fclose(file);
        fclose(outfile);
        printf("Child 2 (PID: %d) - Case inverted, saved in output_inverted.txt\n", getpid());
        return 0;
    }
    
    // Parent waits for both children
    wait(NULL);
    wait(NULL);
    printf("Parent (PID: %d) - Both children completed\n", getpid());
    
    return 0;
}

// Compile: gcc -o q9 q9.c
// Run: ./q9 testfile.txt