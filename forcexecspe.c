/* ==== FILE 1: main_program.c ==== */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    
    printf("Parent Process (PID: %d) starting...\n", getpid());
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // CHILD: Execute the separate program
        printf("Child Process (PID: %d) executing separate program...\n\n", getpid());
        
        // Execute the compiled child program
        // Pass command line arguments if needed
        if (argc > 1) {
            execl("./child_program", "child_program", argv[1], NULL);
        } else {
            execl("./child_program", "child_program", NULL);
        }
        
        // If exec fails
        perror("Exec failed");
        exit(1);
    }
    else {
        // PARENT: Wait for child
        printf("Parent waiting for child to complete...\n");
        wait(NULL);
        printf("\nParent: Child process completed\n");
    }
    
    return 0;
}

/* ==== FILE 2: child_program.c ==== */
/* This is the separate program that child will execute */
/* ADAPT THIS BASED ON WHAT QUESTION ASKS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// OPTION 1: Matrix Row/Column Sum
void matrix_operations() {
    int matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    int row_sum, col_sum;
    
    printf("Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\nRow Sums:\n");
    for (int i = 0; i < 3; i++) {
        row_sum = 0;
        for (int j = 0; j < 3; j++) {
            row_sum += matrix[i][j];
        }
        printf("Row %d: %d\n", i+1, row_sum);
    }
    
    printf("\nColumn Sums:\n");
    for (int j = 0; j < 3; j++) {
        col_sum = 0;
        for (int i = 0; i < 3; i++) {
            col_sum += matrix[i][j];
        }
        printf("Column %d: %d\n", j+1, col_sum);
    }
}

// OPTION 2: String Case Conversion
void string_case_conversion(char *str) {
    printf("Original: %s\n", str);
    printf("Converted: ");
    for (int i = 0; str[i] != '\0'; i++) {
        if (islower(str[i]))
            putchar(toupper(str[i]));
        else if (isupper(str[i]))
            putchar(tolower(str[i]));
        else
            putchar(str[i]);
    }
    printf("\n");
}

// OPTION 3: Count character occurrences
void count_characters(char *str, char ch) {
    int count = 0;
    printf("String: %s\n", str);
    printf("Searching for '%c'\n", ch);
    for (int i = 0; str[i] != '\0'; i++) {
        if (tolower(str[i]) == tolower(ch))
            count++;
    }
    printf("Occurrences: %d\n", count);
}

// OPTION 4: Sum of digits
void sum_of_digits(int num) {
    int sum = 0, temp = num;
    printf("Number: %d\n", num);
    while (temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }
    printf("Sum of digits: %d\n", sum);
}

// OPTION 5: File word/whitespace count
void file_operations(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    
    int words = 0, whitespaces = 0, chars = 0;
    char ch;
    int in_word = 0;
    
    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            whitespaces++;
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            words++;
        }
    }
    
    printf("File: %s\n", filename);
    printf("Total characters: %d\n", chars);
    printf("Total words: %d\n", words);
    printf("Total whitespaces: %d\n", whitespaces);
    
    fclose(fp);
}

int main(int argc, char *argv[]) {
    printf("=== Child Program Executing ===\n\n");
    
    // CHOOSE ONE BASED ON QUESTION:
    
    // For matrix operations:
    matrix_operations();
    
    // For string operations:
    // string_case_conversion("Hello World");
    // count_characters("Programming", 'g');
    
    // For number operations:
    // sum_of_digits(12345);
    
    // For file operations (if filename passed as argument):
    // if (argc > 1) {
    //     file_operations(argv[1]);
    // }
    
    return 0;
}

/*
=== COMPILATION STEPS ===

Step 1: Compile the child program first
gcc child_program.c -o child_program

Step 2: Compile the main program
gcc main_program.c -o main_program

Step 3: Run
./main_program

OR with argument:
./main_program test.txt

=== HOW TO ADAPT FOR EXAM ===

1. Read the question carefully
2. Modify child_program.c to do what's asked
3. Compile child_program.c first
4. Then compile and run main_program.c
5. The child process will execute your child_program

IMPORTANT: 
- The child_program must be compiled BEFORE running main_program
- Use execl("./child_program", ...) to execute it
- You can pass arguments through main_program to child_program
*/