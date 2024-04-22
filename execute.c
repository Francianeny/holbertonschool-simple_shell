#include "shell.h"

int execute_command(char *cmd) {
	    char *argv[MAX_ARGS + 1]; // Maximum number of arguments (+1 for NULL)

    if (strcmp(cmd, "exit") == 0) {
        printf("Exiting shell...\n");
        exit (1);
    }

    if (strcmp(cmd, "env") == 0) {
        print_environment();
        return 0;
    }

    tokenize_input(cmd, argv);

    if (find_and_execute_command(argv) == -1) {
        return -1;
    }

    return 0;
}

int find_and_execute_command(char *argv[]) {
    char *path, *path_copy, *path_token, *command_path;
	int command_found = 0;

	path = _getenv("PATH");
    if (path == NULL) {
        perror("Error getting PATH environment variable");
        return -1;
    }

    path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("Error duplicating PATH string");
        return -1;
    }

    path_token = strtok(path_copy, ":");
    while (path_token != NULL) {
        size_t argv0_length = strlen(argv[0]);
        size_t command_path_length = strlen(path_token) + argv0_length + 2;
        command_path = malloc(command_path_length);
        if (command_path == NULL) {
            perror("Error allocating memory for command_path");
            exit(1);
        }
        sprintf(command_path, "%s/%s", path_token, argv[0]);
        if (access(command_path, X_OK) == 0) {
            command_found = 1;
            execute_command_with_path(command_path, argv);
            free(command_path);
            break;
        }
        free(command_path);
        path_token = strtok(NULL, ":");
    }

    free(path_copy);

    if (!command_found) {
        execute_command_with_path(argv[0], argv);
    }

    return 0;
}

void execute_command_with_path(char *command_path, char *argv[]) {
	int status_child;
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Error fork");
        exit(1);
    }
    if (child_pid == 0) {
        /* Execute the command in the child process */
        if (execve(command_path, argv, NULL) == -1) {
            perror("Error execve");
            exit(1);
        }
    } else {
        /* Wait for the child process to finish in the parent process */
        if (wait(&status_child) == -1) {
            perror("Error wait");
            exit(1);
        }
    }
}
