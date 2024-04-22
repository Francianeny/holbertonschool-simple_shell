#include "shell.h"

int main(void) {
    char *cmd = NULL;
    size_t cmd_buffer_size = 0;
    ssize_t line_length;
    
    while (1) {
        printf("#cisfun$ ");
        line_length = getline(&cmd, &cmd_buffer_size, stdin);

        if (line_length == -1) {
            printf("\n");
            break; // End of input file (Ctrl+D)
        }

        if (cmd[line_length - 1] == '\n') {
            cmd[line_length - 1] = '\0'; // Remove the newline character
        }

        if (execute_command(cmd) == -1) {
            printf("Error executing command\n");
        }
    }

    free(cmd); // Free the dynamically allocated memory for the command line
    return 0;
}
