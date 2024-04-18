#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 80
#define MAX_ARGS 10
/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	pid_t child_pid;
	int status_child, i;
	char *cmd = NULL;
	size_t cmd_buffer_size = 0;
	ssize_t line_length; /* Moved declaration to the beginning of the block */
	/* Declare argv at the beginning of the block */
	char *argv[MAX_ARGS + 1]; /* Maximum number of arguments (+1 for NULL) */
	while (1)
	{
		printf("#cisfun$ ");
		line_length = getline(&cmd, &cmd_buffer_size, stdin);
		if (line_length == -1)
		{
			printf("\n");
			break; /* End of input file (Ctrl+D) */
		}
		if (cmd[line_length - 1] == '\n')
			cmd[line_length - 1] = '\0'; /* Remove the newline character */
		/* Tokenize the input */
		i = 0;
		argv[i] = strtok(cmd, " ");
		while (argv[i] != NULL && i < MAX_ARGS)
		{
			i++;
			argv[i] = strtok(NULL, " ");
		}
		argv[i] = NULL;
		/* Create a child process and execute the command */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error fork");
			exit(1);
		}
		if (child_pid == 0)
		{
			/* Execute the command in the child process */
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error execve");
				exit(1);
			}
		}
		else
		{
			/* Wait for the child process to finish in the parent process */
			if (wait(&status_child) == -1)
			{
				perror("Error wait");
				exit(1);
			}
		}
	}
	free(cmd); /* Free the dynamically allocated memory for the command line */
	return (0);
}
