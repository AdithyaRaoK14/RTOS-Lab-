// Q11: Create two threads displaying different messages
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_one(void* arg) {
    printf("This is thread one\n");
    return NULL;
}

void* thread_two(void* arg) {
    printf("This is thread two\n");
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    
    printf("Main thread (PID: %d) - Creating threads...\n", getpid());
    
    // Create first thread
    if (pthread_create(&tid1, NULL, thread_one, NULL) != 0) {
        printf("Failed to create thread 1\n");
        return 1;
    }
    
    // Create second thread
    if (pthread_create(&tid2, NULL, thread_two, NULL) != 0) {
        printf("Failed to create thread 2\n");
        return 1;
    }
    
    // Wait for both threads to complete
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("Main thread - Both threads completed\n");
    
    return 0;
}

// Compile: gcc -o q11 q11.c -lpthread
// Run: ./q11