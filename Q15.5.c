// Q15 Child Program 4: Count words in a file
// File: q15_child_wordcount.c

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main() {
    FILE *file;
    char filename[100];
    char ch, prev = ' ';
    int word_count = 0;
    
    printf("=== Word Count Program ===\n");
    printf("Child Process PID: %d\n\n", getpid());
    
    printf("Enter filename: ");
    scanf("%s", filename);
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
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
    
    printf("\nFile: %s\n", filename);
    printf("Total words: %d\n", word_count);
    
    return 0;
}

// Compile: gcc -o q15_child_wordcount q15_child_wordcount.c