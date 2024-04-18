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
    int status_child, i;
    char cmd[MAX_LINE_LENGTH];
    char **argv;

    while (1)
    {
        printf("#cisfun$ ");
        // Read a line of text from stdin using getline
        if (fgets(cmd, MAX_LINE_LENGTH, stdin) == NULL)
        {
            // Condition EOF (Ctrl+D)
            printf("\n");
            break;
        }

        // Tokenize the input
        i = 0;
        argv = malloc((MAX_LINE_LENGTH / 2 + 1) * sizeof(char *));
        if (argv == NULL)
        {
            perror("Error malloc");
            exit(1);
        }

        argv[i] = strtok(cmd, " \n");
        while (argv[i] != NULL)
        {
            i++;
            argv[i] = strtok(NULL, " \n");
        }
        argv[i] = NULL;

        // Create a child process and execute the command
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error fork");
            exit(1);
        }
        if (child_pid == 0)
        {
            // Exécuter la commande dans le processus enfant
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("./shell");
                exit(1);
            }
        }
        else
        {
            // Wait for the child process to finish in the parent process
            if (wait(&status_child) == -1)
            {
                perror("Error wait");
                exit(1);
            }
        }

        // Free the dynamically allocated memory for the command line
        free(argv);
    }

    return 0;
}
