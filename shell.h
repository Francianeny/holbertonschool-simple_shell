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
#define MAX_ARGS 64
#define MAX_COMMAND_PATH_LENGTH 256

extern char **environ;

char *_getenv(const char *name);
void print_environment(void);
void tokenize_input(char *cmd, char *argv[]);
int find_and_execute_command(char *argv[], char *av[], int line_n);
int search_and_exec_cmd(char *path_copy, char *argv[], char *av[], int line_n);
void exec_cmd_with_path(char *cmd_path, char *argv[], char *av[], int line_n);
int execute_command(char *cmd, char *av[], int line_n);

#endif /* SHELL_H */
