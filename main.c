#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 80

int main(void)
{
    pid_t child_pid;
    int status_child;
    char cmd[MAX_LINE_LENGTH];
    char *argv[] = {cmd, NULL};

    while (1)
    {
        printf("#cisfun$ ");

        fgets(cmd, MAX_LINE_LENGTH, stdin);

        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error fork");
            return (1);
        }
        if (child_pid == 0)
        {
            // Execute the command in the child process
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("Error execve");
                return (1);
            }
        }
        else
        {
            // Wait for the child process to finish in the parent process
            if (wait(&status_child) == -1)
            {
                perror("Error wait");
                return (1);
            }
        }
    }
    return (0);
}


