#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <libgen.h>
#include <limits.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 10
#define MAX_COMMAND_PATH_LENGTH 256

extern char **environ;

char *_getenv(const char *name);
void print_environment(void);
void tokenize_input(char *cmd, char *argv[]);
int find_and_execute_command(char *argv[]);
void execute_command_with_path(char *command_path, char *argv[]);
int execute_command(char *cmd);

#endif /* SHELL_H */
