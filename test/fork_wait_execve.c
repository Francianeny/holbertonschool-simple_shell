#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Creates 5 child processes to execute the command "ls -l /tmp".
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t child_pid;
    int status_child;
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

    // Create 5 child processes
    for (int i = 0; i < 5; i++)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error:");
            return (1);
        }
        if (child_pid == 0)
        {
            // Execute the command in the child process
            if (execve("/bin/ls", argv, NULL) == -1)
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
