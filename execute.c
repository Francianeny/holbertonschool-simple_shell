#include "shell.h"

/**
 * tokenize_input - Tokenize the input command
 * @cmd: The input command string
 * @argv: Array to store the tokenized command arguments
 */
void tokenize_input(char *cmd, char *argv[])
{
	int i = 0;

	while (*cmd != '\0' && *cmd == ' ')
	{
		cmd++;
	}
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
		exit(0);
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
	char *path, *path_copy;
	int result;

	path = _getenv("PATH");
	if (path == NULL)
	{
		perror("Error getting PATH environment variable");
		return (1);
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("Error duplicating PATH string");
		free(path);
		return (1);
	}
	else
	result = search_and_execute_command(path_copy, argv);
	free(path_copy);
	return (result);
}

/**
 * search_and_execute_command - Search for the command in the PATH
 * @path_copy: Copy of the PATH environment variable
 * @argv: Array of command arguments
 *
 * Return: 0 on success, 1 on failure
 */
int search_and_execute_command(char *path_copy, char *argv[])
{
	char *path_token;
    int command_found = 0;

    if (path_copy == NULL || argv == NULL || argv[0] == NULL)
    {
        fprintf(stderr, "Invalid input parameters\n");
        return -1;
    }

    path_token = strtok(path_copy, ":");

    while (path_token != NULL)
    {
        size_t argv0_length = strlen(argv[0]);
        size_t path_token_length = strlen(path_token);
        size_t command_path_length = path_token_length + argv0_length + 2;
        char *command_path;

        if (command_path_length >= MAX_COMMAND_PATH_LENGTH)
        {
            fprintf(stderr, "Error: Command path length exceeds maximum\n");
            return (-1);
        }

        command_path = malloc(command_path_length);
        if (command_path == NULL)
        {
            perror("Error allocating memory for command_path");
            return (-1);
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
	char *gwd = getcwd(cwd, sizeof(cwd));
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error fork");
		free(command_path);
		exit(1);
		}
	if (child_pid == 0) /* Execute the command in the child process */
	{
		if (execve(command_path, argv, NULL) == -1)
		{
			if (gwd != NULL)
			{
				count++;
				fprintf(stderr, "%s: %d: %s: not found\n", gwd, count, argv[0]);
				free(gwd);
			}
			else
			{
				perror("Error getting current directory");
			}
			free(command_path);
			exit(127);

		}
	}
	else /* Wait for the child process to finish in the parent process */
	{
		if (wait(&status_child) == -1)
		{
			perror("Error wait");
			free(command_path);
			exit(127);
		}
	}
	/*free(command_path);*/
}
