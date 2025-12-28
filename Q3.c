// Q3: Parent creates 4 children executing ls, ls -l, pwd, date
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;
    
    for (i = 0; i < 4; i++) {
        pid = fork();
        
        if (pid < 0) {
            printf("Fork failed\n");
            return 1;
        }
        else if (pid == 0) {
            // Child process
            printf("\n=== Child %d (PID: %d) ===\n", i+1, getpid());
            
            switch(i) {
                case 0:
                    printf("Executing: ls\n");
                    execlp("ls", "ls", NULL);
                    break;
                case 1:
                    printf("Executing: ls -l\n");
                    execlp("ls", "ls", "-l", NULL);
                    break;
                case 2:
                    printf("Executing: pwd\n");
                    execlp("pwd", "pwd", NULL);
                    break;
                case 3:
                    printf("Executing: date\n");
                    execlp("date", "date", NULL);
                    break;
            }
            
            printf("execlp failed for child %d\n", i+1);
            return 1;
        }
    }
    
    // Parent waits for all children
    for (i = 0; i < 4; i++) {
        wait(NULL);
    }
    
    printf("\nParent: All children completed\n");
    return 0;
}