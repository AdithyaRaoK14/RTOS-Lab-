// Q14: Thread 1 writes numbers, Thread 2 reads and calculates sum
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 10

int shared_numbers[SIZE];
int sum = 0;
pthread_mutex_t lock;

void* thread_one(void* arg) {
    pthread_mutex_lock(&lock);
    
    printf("Thread 1: Writing numbers to shared memory\n");
    for (int i = 0; i < SIZE; i++) {
        shared_numbers[i] = i + 1;  // Numbers 1 to 10
        printf("%d ", shared_numbers[i]);
    }
    printf("\n");
    
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* thread_two(void* arg) {
    // Wait for thread 1 to write
    sleep(1);
    
    pthread_mutex_lock(&lock);
    
    printf("\nThread 2: Reading numbers from shared memory\n");
    printf("Numbers: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", shared_numbers[i]);
        sum += shared_numbers[i];
    }
    printf("\n");
    
    printf("Thread 2: Sum of numbers = %d\n", sum);
    
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    
    // Initialize mutex
    pthread_mutex_init(&lock, NULL);
    
    printf("Main thread - Creating threads...\n\n");
    
    // Create threads
    if (pthread_create(&tid1, NULL, thread_one, NULL) != 0) {
        printf("Failed to create thread 1\n");
        return 1;
    }
    
    if (pthread_create(&tid2, NULL, thread_two, NULL) != 0) {
        printf("Failed to create thread 2\n");
        return 1;
    }
    
    // Wait for both threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    // Destroy mutex
    pthread_mutex_destroy(&lock);
    
    printf("\nMain thread - Both threads completed\n");
    printf("Final sum displayed by Thread 2: %d\n", sum);
    
    return 0;
}

// Compile: gcc -o q14 q14.c -lpthread
// Run: ./q14