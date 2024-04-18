#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// the line variable contains the command line /bin/ls -l
char *line = "/bin/ls -l";
char *token;
char *args[10];
int i = 0;

// parse the command line into separate arguments, i use strtok
token = strtok(line, " "); // The first token is returned and stored in the token variable.
while (token != NULL) // loop continues as long as there are other tokens to process
{
    args[i] = token;
    i++;
    token = strtok(NULL, " "); // continue to process the same chain as before
}
args[i] = NULL; // which indicates the end of the argument list.

// once have the arguments, run the command, i use execve
// fork used to create a new process
pid_t pid;
pid = fork();
if (pid == 0)
{
    execve(args[0], args, NULL);
    perror("execve failed");
    exit(1);
}
else if (pid < 0) // is used to verify the fork function has failed
{
    perror("fork failed"); // is used to print an error message
    exit(1);
}
else
{
    wait(&status); // is used to wait for the end of the child process
}
