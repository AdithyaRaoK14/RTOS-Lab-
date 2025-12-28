#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// Shared memory area
char shared_string[100] = "";
int shared_numbers[10];
int shared_sum = 0;
int data_ready = 0; // Flag for synchronization

// Thread function 1: Simple message display
void* thread_one(void* arg) {
    printf("This is thread one\n");
    
    // Write to shared memory
    strcpy(shared_string, "Hello There");
    printf("Thread 1: Wrote '%s' to shared memory\n", shared_string);
    data_ready = 1; // Signal data is ready
    
    // Wait for thread 2 to process
    sleep(1);
    
    // Read back inverted case
    printf("Thread 1: Read back from shared memory: '%s'\n", shared_string);
    
    return NULL;
}

// Thread function 2: Message display and case conversion
void* thread_two(void* arg) {
    printf("This is thread two\n");
    
    // Wait for data to be ready
    while (!data_ready) {
        usleep(1000); // Small delay
    }
    
    // Read and display
    printf("Thread 2: Read '%s' from shared memory\n", shared_string);
    
    // Convert case
    for (int i = 0; shared_string[i] != '\0'; i++) {
        if (islower(shared_string[i])) {
            shared_string[i] = toupper(shared_string[i]);
        } else if (isupper(shared_string[i])) {
            shared_string[i] = tolower(shared_string[i]);
        }
    }
    
    printf("Thread 2: Converted case to '%s'\n", shared_string);
    
    return NULL;
}

// Thread for number sum calculation
void* number_writer(void* arg) {
    printf("\nNumber Writer Thread: Writing numbers to shared memory\n");
    for (int i = 0; i < 10; i++) {
        shared_numbers[i] = (i + 1) * 10; // 10, 20, 30...100
        printf("%d ", shared_numbers[i]);
    }
    printf("\n");
    data_ready = 2; // Signal for sum calculation
    return NULL;
}

void* number_reader(void* arg) {
    // Wait for numbers to be written
    while (data_ready != 2) {
        usleep(1000);
    }
    
    printf("Number Reader Thread: Reading and calculating sum\n");
    for (int i = 0; i < 10; i++) {
        shared_sum += shared_numbers[i];
    }
    printf("Sum of numbers: %d\n", shared_sum);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;
    
    printf("=== PART 1: String Operations ===\n");
    
    // Create threads for string operations
    pthread_create(&t1, NULL, thread_one, NULL);
    pthread_create(&t2, NULL, thread_two, NULL);
    
    // Wait for threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("\n=== PART 2: Number Sum Calculation ===\n");
    data_ready = 0; // Reset flag
    
    // Create threads for number operations
    pthread_create(&t3, NULL, number_writer, NULL);
    pthread_create(&t4, NULL, number_reader, NULL);
    
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    
    printf("\n=== All threads completed ===\n");
    
    return 0;
}

/*
COMPILATION: gcc -pthread program.c -o program
EXECUTION: ./program

KEY CONCEPTS:
1. Global variables = shared memory between threads
2. pthread_create() creates a thread
3. pthread_join() waits for thread to finish
4. Use flags (data_ready) for simple synchronization
5. For better sync, use mutexes (pthread_mutex_t)

COVERS:
- Q11: Thread message display
- Q12: String sharing and case conversion
- Q14: Number array sum calculation
*/