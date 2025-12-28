// Q15 Child Program 5: Count whitespaces (blanks, tabs, newlines) in a file
// File: q15_child_whitespace.c

#include <stdio.h>
#include <unistd.h>

int main() {
    FILE *file;
    char filename[100];
    char ch;
    int blanks = 0, tabs = 0, newlines = 0;
    
    printf("=== Whitespace Count Program ===\n");
    printf("Child Process PID: %d\n\n", getpid());
    
    printf("Enter filename: ");
    scanf("%s", filename);
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ') {
            blanks++;
        } else if (ch == '\t') {
            tabs++;
        } else if (ch == '\n') {
            newlines++;
        }
    }
    
    fclose(file);
    
    printf("\nFile: %s\n", filename);
    printf("Blanks (spaces): %d\n", blanks);
    printf("Tabs: %d\n", tabs);
    printf("Newlines: %d\n", newlines);
    printf("Total whitespaces: %d\n", blanks + tabs + newlines);
    
    return 0;
}

// Compile: gcc -o q15_child_whitespace q15_child_whitespace.c