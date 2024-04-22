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
	int status_child, i, command_found;
	char *cmd = NULL;
	size_t cmd_buffer_size = 0;
	ssize_t line_length;

	char *argv[MAX_ARGS + 1]; /* Maximum number of arguments (+1 for NULL) */
	char *path;
	char *path_copy;
	char *path_token;

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

		/* Check if the command exists in PATH */
		path = getenv("PATH");
		if (path == NULL)
		{
			perror("Error getting PATH environment variable");
			exit(1);
		}

		path_copy = strdup(path);
		if (path_copy == NULL)
		{
			perror("Error duplicating PATH string");
			exit(1);
		}

		/* Search in PATH */
		path_token = strtok(path_copy, ":");
		command_found = 0;
		while (path_token != NULL)
		{
			/* Calculate the length of argv[0] if it exists */
			size_t argv0_length = argv[0] ? strlen(argv[0]) : 0;

			/* Calculate the total length needed for command_path */
			size_t command_path_length = strlen(path_token) + argv0_length + 2;

			/* Allocate memory for command_path */
			char *command_path = malloc(command_path_length);
			if (command_path == NULL)
			{
				perror("Error allocating memory for command_path");
				exit(1);
			}

			/* Construct the command path */
			sprintf(command_path, "%s/%s", path_token, argv[0]);

			/* Check if the command path exists and is executable */
			if (access(command_path, X_OK) == 0)
			{
				command_found = 1;
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
					if (execve(command_path, argv, NULL) == -1)
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
				free(command_path);
				break;
			}
			free(command_path);
			path_token = strtok(NULL, ":");
		}

		free(path_copy);

		/* If command is not found in PATH, try executing as a system command */
		if (!command_found)
		{
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
	}
	free(cmd); /* Free the dynamically allocated memory for the command line */
	return (0);
}
