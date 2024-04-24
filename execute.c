#include "shell.h"

/**
 * tokenize_input - Tokenize the input command
 * @cmd: The input command string
 * @argv: Array to store the tokenized command arguments
 */
void tokenize_input(char *cmd, char *argv[])
{
	int i = 0;

	argv[i] = strtok(cmd, " ");
	while (argv[i] != NULL && i < MAX_ARGS)
	{
		i++;
		argv[i] = strtok(NULL, " ");
	}
	argv[i] = NULL;
}

/**
 * execute_command - Execute the given command
 * @cmd: The command string to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *cmd)
{
	char *argv[MAX_ARGS + 1]; /* Maximum number of arguments (+1 for NULL)*/

	if (strcmp(cmd, "exit") == 0)
	{
		exit (0);
	}

	if (strcmp(cmd, "env") == 0)
	{
		print_environment();
		return (0);
	}

	tokenize_input(cmd, argv);

	if (find_and_execute_command(argv) == -1)
	{
		return (-1);
	}

	return (0);
}

/**
 * find_and_execute_command - Find and execute the command
 * @argv: Array of command arguments
 *
 * Return: 0 on success, 1 on failure
 */
int find_and_execute_command(char *argv[])
{
	char *path, *path_copy, *path_token, *command_path;
	int command_found = 0;

	path = _getenv("PATH");
	if (path == NULL)
	{
		perror("Error getting PATH environment variable");
		return (1);
	}

	path_copy = _strdup(path);
	if (path_copy == NULL)
	{
		perror("Error duplicating PATH string");
		return (1);
	}

	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		size_t argv0_length = strlen(argv[0]);
		size_t command_path_length = strlen(path_token) + argv0_length + 2;
		command_path = malloc(command_path_length);
		if (command_path == NULL)
		{
			perror("Error allocating memory for command_path");
			exit(127);
		}
		sprintf(command_path, "%s/%s", path_token, argv[0]);
		if (access(command_path, X_OK) == 0)
		{
			command_found = 1;
			execute_command_with_path(command_path, argv);
			free(command_path);
			break;
		}
		free(command_path);
		path_token = strtok(NULL, ":");
	}

	free(path_copy);

	if (!command_found)
	{
		execute_command_with_path(argv[0], argv);
	}

	return (0);
}

/**
 * execute_command_with_path - Execute the command with the specified path
 * @command_path: Full path of the command to execute
 * @argv: Array of command arguments
 */
void execute_command_with_path(char *command_path, char *argv[])
{
	int status_child;
	int count = 0;
	char cwd[PATH_MAX];
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error fork");
		exit(127);
	}
	if (child_pid == 0)
	{
		/* Execute the command in the child process */
		if (execve(command_path, argv, NULL) == -1)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				count++;
				fprintf(stderr, "%s: %d: %s: not found\n", cwd, count, argv[0]);
			}
			else
			{
				perror("Error getting current directory");
			}
			exit(127);
		}
	}
	else
	{
		/* Wait for the child process to finish in the parent process */
		if (wait(&status_child) == -1)
		{
			perror("Error wait");
			exit(256);
		}
	}
}
