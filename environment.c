#include "shell.h"

/**
 * _getenv - Get the value of an environment variable
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	char **env = environ;
	int name_len = strlen(name);

	if (name == NULL || environ == NULL)
		return (NULL);

	while (*env != NULL)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (*env + name_len + 1); /* Return the value after '=' */
		}
		env++;
	}
	return (NULL);
}

/**
 * print_environment - Print the environment variables
 */
void print_environment(void)
{
	char **env_var = environ;

	while (*env_var != NULL)
	{
		printf("%s\n", *env_var);
		env_var++;
	}
}
