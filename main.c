#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
		char *cmd = NULL;
		size_t cmd_buffer_size = 0;
		ssize_t line_length;
		int is_interactive = isatty(STDIN_FILENO);

		while (1)
		{
				if (is_interactive)
				{
						printf("($) ");
				}
				line_length = getline(&cmd, &cmd_buffer_size, stdin);

				if (line_length == -1)
				{
						if (is_interactive)
						{
								printf("\n");
								exit (1); /* End of input file (Ctrl+D) */
						}
						else
						{
								exit (1); /* End of input file (Ctrl+D) */
						}
				}
				if (line_length <= 1)
				{
						/* If the line is empty or contains only a newline character */
						continue;
				}

				if (cmd[line_length - 1] == '\n')
				{
						cmd[line_length - 1] = '\0'; /* Remove the newline character */
				}

				if (execute_command(cmd) == -1)
				{
						printf("Error executing command\n");
				}
		}

		free(cmd); /* Free the dynamically allocated memory for the command line */
		return (0);
}
