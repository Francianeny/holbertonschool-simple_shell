#include "shell.h"

char *_getenv(const char *name) {
    char **env = environ;
    int name_len = strlen(name);

    while (*env != NULL) {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=') {
            return &(*env)[name_len + 1]; /* Return the value after '=' */
        }
        env++;
    }
    return NULL;
}

void print_environment(void) {
    char **env_var = environ;

    while (*env_var != NULL) {
        printf("%s\n", *env_var);
        env_var++;
    }
}

void tokenize_input(char *cmd, char *argv[]) {
    int i = 0;
    
    argv[i] = strtok(cmd, " ");
    while (argv[i] != NULL && i < MAX_ARGS) {
        i++;
        argv[i] = strtok(NULL, " ");
    }
    argv[i] = NULL;
}
