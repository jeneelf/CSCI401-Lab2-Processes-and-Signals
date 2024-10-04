#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_ITERATIONS 30
#define MAX_SLEEP_TIME 10

void childProcess() {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    int iterations = rand() % (MAX_ITERATIONS + 1);
    int i; // Declare the loop variable here

    for (i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", pid);
        int sleep_time = rand() % (MAX_SLEEP_TIME + 1);
        sleep(sleep_time);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", pid, ppid);
    }

    exit(0);
}

int main(void) {
    srandom(time(NULL)); // Seed the random number generator

    pid_t child1, child2;

    // Create first child process
    child1 = fork();
    if (child1 == 0) {
        childProcess(); // In child process
    }

    // Create second child process
    child2 = fork();
    if (child2 == 0) {
        childProcess(); // In child process
    }

    // Parent process waits for both children to complete
    int status;
    int i; // Declare the loop variable here
    for (i = 0; i < 2; i++) {
        pid_t child_pid = wait(&status);
        printf("Child Pid: %d has completed\n", child_pid);
    }

    return 0;
}
