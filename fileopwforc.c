#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    
    char *filename = argv[1];
    pid_t pid1, pid2;
    
    // Create first child
    pid1 = fork();
    
    if (pid1 == 0) {
        // CHILD 1: Count lines (or words, or 'a' characters)
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            perror("Error opening file in child 1");
            exit(1);
        }
        
        int line_count = 0;
        int word_count = 0;
        int char_a_count = 0;
        char ch;
        int in_word = 0;
        
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '\n') line_count++;
            if (ch == 'a' || ch == 'A') char_a_count++;
            
            // Word counting logic
            if (ch == ' ' || ch == '\n' || ch == '\t') {
                in_word = 0;
            } else if (in_word == 0) {
                in_word = 1;
                word_count++;
            }
        }
        
        printf("Child 1 Results:\n");
        printf("Total lines: %d\n", line_count);
        printf("Total words: %d\n", word_count);
        printf("Total 'a' characters: %d\n", char_a_count);
        
        fclose(fp);
        exit(0);
    }
    
    // Create second child
    pid2 = fork();
    
    if (pid2 == 0) {
        // CHILD 2: Count characters (or convert case, or invert case)
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            perror("Error opening file in child 2");
            exit(1);
        }
        
        int char_count = 0;
        char ch;
        
        printf("\nChild 2 Results:\n");
        printf("Total characters: ");
        
        while ((ch = fgetc(fp)) != EOF) {
            char_count++;
        }
        
        printf("%d\n", char_count);
        fclose(fp);
        
        // OPTION: Convert lowercase to uppercase
        // (Write to a new file or display)
        fp = fopen(filename, "r");
        printf("\nConverted to uppercase:\n");
        while ((ch = fgetc(fp)) != EOF) {
            putchar(toupper(ch));
        }
        printf("\n");
        fclose(fp);
        
        exit(0);
    }
    
    // Parent waits for both children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    printf("\nParent: Both children completed\n");
    
    return 0;
}

/*
COMPILATION: gcc program.c -o program
EXECUTION: ./program sample.txt

CREATE TEST FILE:
echo -e "Hello World\nThis is a test\nWith multiple lines" > sample.txt

ADAPTATIONS FOR DIFFERENT QUESTIONS:
- Q7: Count lines (child1) and characters (child2)
- Q8: Convert to uppercase (child1) and count 'a's (child2)
- Q9: Count words (child1) and invert case (child2)

To invert case, replace toupper() with:
    if (islower(ch)) putchar(toupper(ch));
    else if (isupper(ch)) putchar(tolower(ch));
    else putchar(ch);
*/