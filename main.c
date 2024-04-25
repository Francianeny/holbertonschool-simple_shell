#include "shell.h"

/**
 * main - Entry point of the shell program
 * @ac: Number of command-line arguments.
 * @av: Array of command-line arguments.
 *
 * Return: Always 0
 */
int main(int ac, char *av[])
{
	int line_n = 1;
	char *cmd = NULL;
	size_t cmd_buffer_size = 0;
	ssize_t line_length;
	int is_interactive = isatty(STDIN_FILENO);
	(void)ac;


	while (1)
	{
		if (is_interactive)
			printf("($) ");

		line_length = getline(&cmd, &cmd_buffer_size, stdin);
		if (line_length == -1)
		{
			free(cmd);
			if (is_interactive)
			{
				printf("\n");
				exit(0); /* End of input file (Ctrl+D) in no interactive mode */
			}
			else
				exit(0); /* (Ctrl+D) in interactive mode */
		}
		if (line_length <= 1)
		{
			free(cmd);
			continue;/* If line is empty or contains only a newline character */
		}
		if (cmd[line_length - 1] == '\n')
			cmd[line_length - 1] = '\0'; /* Remove the newline character */

		if (execute_command(cmd, av, line_n) == -1)
			printf("Error executing command\n");
		line_n++;
	}
	free(cmd); /* Free the dynamically allocated memory for the command line */
	cmd = NULL;
	cmd_buffer_size = 0;
	return (0);
}
