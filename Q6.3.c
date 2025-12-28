// q6_odd.c - Odd series program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n, i;
    
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }
    
    n = atoi(argv[1]);
    
    if (n <= 0) {
        printf("Please enter a positive number\n");
        return 1;
    }
    
    printf("Parent Process (PID: %d) - Odd Series:\n", getpid());
    for (i = 0; i < n; i++) {
        printf("%d ", 2 * i + 1);
    }
    printf("\n");
    
    return 0;
}

// Compile: gcc -o q6_odd q6_odd.c