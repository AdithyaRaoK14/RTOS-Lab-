// Q2: Parent fork, child execute ls command with/without wait()
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    printf("===== WITH wait() =====\n");
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child executing ls command:\n");
        execlp("ls", "ls", NULL);
        printf("execlp failed\n");
    }
    else {
        // Parent process
        wait(NULL);  // Wait for child to complete
        printf("Parent: Child completed\n");
    }
    
    printf("\n===== WITHOUT wait() =====\n");
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child executing ls command:\n");
        execlp("ls", "ls", NULL);
        printf("execlp failed\n");
    }
    else {
        // Parent process - no wait()
        printf("Parent: Not waiting for child\n");
    }
    
    return 0;
}

/* Observation:
 * WITH wait(): Parent waits for child to finish, output is ordered
 * WITHOUT wait(): Parent may finish before child, output may be interleaved
 * Child may become orphan if parent exits first
 */