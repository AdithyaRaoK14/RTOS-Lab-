// Q15 Child Program 2: Change case of characters in a string
// File: q15_child_string.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main() {
    char str[200];
    int i;
    
    printf("=== String Case Conversion Program ===\n");
    printf("Child Process PID: %d\n\n", getpid());
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline if present
    str[strcspn(str, "\n")] = '\0';
    
    printf("\nOriginal string: %s\n", str);
    
    // Convert case (lowercase to uppercase and vice versa)
    for (i = 0; str[i] != '\0'; i++) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        } else if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
    
    printf("After case conversion: %s\n", str);
    
    return 0;
}

// Compile: gcc -o q15_child_string q15_child_string.c