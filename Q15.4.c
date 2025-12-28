// Q15 Child Program 3: Find sum of digits of a number
// File: q15_child_digits.c

#include <stdio.h>
#include <unistd.h>

int main() {
    int num, original, sum = 0, digit;
    
    printf("=== Sum of Digits Program ===\n");
    printf("Child Process PID: %d\n\n", getpid());
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    original = num;
    
    // Handle negative numbers
    if (num < 0) {
        num = -num;
    }
    
    while (num > 0) {
        digit = num % 10;
        sum += digit;
        num /= 10;
    }
    
    printf("\nNumber: %d\n", original);
    printf("Sum of digits: %d\n", sum);
    
    return 0;
}

// Compile: gcc -o q15_child_digits q15_child_digits.c