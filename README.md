# C - Simple Shell

### What is the shell ? :
The shell is a program that takes commands from the keyboard via the terminal, and gives them to the operating system to perform. To better understand how the shell actually works, you can read  [Médium](https://medium.com/@winfrednginakilonzo/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd)

### About this project:
This project is a simple version of the linux shell made for Holberton School taking part of the "Low-level programming & Algorithm - Linux and Unix system programming" projects.
It is created using the C programming Language and it can do many functionalities that a real shell does.

### Essential Functionalities of the Simple Shell:
Displays a prompt "#cisfun$ " and waits for user input.
Runs all commands of type "executable program" (ls and /bin/ls).
Runs the following build_in commands: exit, env, setenv and unsetenv.
Handles commands with arguments.
Handles the PATH global variable.
Handles The EOF (End Of File) condition.
Handles the Ctrl + C signal -> It doesn't exit the shell

### Files description:

1. **AUTHORS** :  This file lists all individuals having contributed content to the repository
<p>GuerinTifenn <8807@holbertonstudents.com><br>
Francianeny <8877@holbertonstudents.com></p>

 2. **man_1_simple_shell** : Manual page for the simple_shell

3. **shell.h** : Header file

4. **environnement.c** :
<p>_getenv -> Get the value of an environment variable<br>
_strncmp -> Takes as parameters the two strings to compare<br>
 print_environment -> Print the environment variables<br>
_strdup -> Copy a string and returns pointer to a allocated space in memory

5. **execute.c** :
tokenize_input -> Tokenize the input command
execute_command -> Execute the given command
find_and_execute_command -> Find and execute the command
_sprintf -> write formatted data into a string
execute_command_with_path -> Execute the command with the specified path

6. **main.c** :
The main entry point for the example.


### List of allowed functions and system calls+ :

- all functions from string.h
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- printf (man 3 printf)
- fprintf (man 3 fprintf)
- vfprintf (man 3 vfprintf)
- sprintf (man 3 sprintf)
- putchar (man 3 putchar)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

### Usage :

You can try your shell by following these steps:

-  ***step 1*** : Clone our repository using this command, (you need to have git installed on your machine first)

> git clone https://github.com/Francianeny/simple_shell


-  ***step 2*** : Change directory to simple_shell:

> cd simple_shell

- ***Step 3*** : Change directory to simple_shell:

> gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

- ***Step 4*** : Compile the C files in this way:

> ./hsh

**Exiting the shell** When you want to exit the shell, you can use one of the following methods:

1. Type the command "exit"

> exit

2. Press on Ctrl + D

> ![alt text](<Capture d'écran 2024-04-23 150337.png>)















