// Q12: Shared memory between threads - write, read, convert case
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

char shared_memory[100];
pthread_mutex_t lock;

void* thread_one(void* arg) {
    // Thread 1: Write string to shared memory
    pthread_mutex_lock(&lock);
    strcpy(shared_memory, "Hello There");
    printf("Thread 1: Wrote '%s' to shared memory\n", shared_memory);
    pthread_mutex_unlock(&lock);
    
    // Wait for thread 2 to process
    sleep(2);
    
    // Read back the modified string
    pthread_mutex_lock(&lock);
    printf("Thread 1: Read back '%s' from shared memory\n", shared_memory);
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

void* thread_two(void* arg) {
    // Wait for thread 1 to write
    sleep(1);
    
    // Thread 2: Read string from shared memory
    pthread_mutex_lock(&lock);
    printf("Thread 2: Read '%s' from shared memory\n", shared_memory);
    
    // Convert case (lowercase to uppercase and vice versa)
    for (int i = 0; shared_memory[i] != '\0'; i++) {
        if (islower(shared_memory[i])) {
            shared_memory[i] = toupper(shared_memory[i]);
        } else if (isupper(shared_memory[i])) {
            shared_memory[i] = tolower(shared_memory[i]);
        }
    }
    
    printf("Thread 2: Converted to '%s' in shared memory\n", shared_memory);
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    
    // Initialize mutex
    pthread_mutex_init(&lock, NULL);
    
    printf("Main thread - Creating threads...\n\n");
    
    // Create threads
    pthread_create(&tid1, NULL, thread_one, NULL);
    pthread_create(&tid2, NULL, thread_two, NULL);
    
    // Wait for both threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    // Destroy mutex
    pthread_mutex_destroy(&lock);
    
    printf("\nMain thread - Both threads completed\n");
    
    return 0;
}

// Compile: gcc -o q12 q12.c -lpthread
// Run: ./q12