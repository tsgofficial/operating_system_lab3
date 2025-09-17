// zombie.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {
        // Child exits quickly
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);
    }
    else
    {
        // Parent sleeps to keep zombie around
        printf("Parent process (PID: %d), child PID: %d\n", getpid(), pid);
        printf("Run `ps -l` in another terminal to see the zombie.\n");
        sleep(10);
    }

    return 0;
}
