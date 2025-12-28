#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Structure to pass data to thread
typedef struct {
    int current_level;
    int max_levels;
} ThreadData;

// Thread function that recursively creates threads
void* thread_function(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int current = data->current_level;
    int max = data->max_levels;
    
    // Print thread info
    printf("Thread ID: %lu, Recursion Level: %d\n", 
           pthread_self(), current);
    
    // Base case: stop if reached max levels
    if (current >= max) {
        free(data);
        return NULL;
    }
    
    // Recursive case: create next thread
    pthread_t new_thread;
    ThreadData* new_data = (ThreadData*)malloc(sizeof(ThreadData));
    new_data->current_level = current + 1;
    new_data->max_levels = max;
    
    // Create the next thread
    if (pthread_create(&new_thread, NULL, thread_function, new_data) != 0) {
        printf("Error creating thread at level %d\n", current + 1);
        free(new_data);
        free(data);
        return NULL;
    }
    
    // Wait for the thread to complete
    pthread_join(new_thread, NULL);
    
    free(data);
    return NULL;
}

int main() {
    int num_levels;
    
    // Take input from keyboard
    printf("Enter the number of recursive thread levels: ");
    scanf("%d", &num_levels);
    
    // Validate input
    if (num_levels <= 0) {
        printf("Please enter a positive number\n");
        return 1;
    }
    
    printf("\n--- Starting Recursive Thread Creation ---\n\n");
    
    // Create first thread data
    ThreadData* initial_data = (ThreadData*)malloc(sizeof(ThreadData));
    initial_data->current_level = 1;
    initial_data->max_levels = num_levels;
    
    // Create first thread
    pthread_t first_thread;
    if (pthread_create(&first_thread, NULL, thread_function, initial_data) != 0) {
        printf("Error creating first thread\n");
        free(initial_data);
        return 1;
    }
    
    // Wait for first thread to complete
    pthread_join(first_thread, NULL);
    
    printf("\n--- All threads completed ---\n");
    
    return 0;
}

/* 
COMPILATION:
gcc -pthread program.c -o program

EXECUTION:
./program
*/