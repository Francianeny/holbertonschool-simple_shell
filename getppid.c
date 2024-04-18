#include <stdio.h>
#include <unistd.h>

int main ()
{
    pid_t my_pid;
    my_pid = getppid();
    printf ("Le PID du processus parent est : %d\n", my_pid);
    return (0);
}
