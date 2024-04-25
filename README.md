# C - Simple Shell

### <font color=blue>What is the shell ? :</font>

The shell is a program that takes commands from the keyboard via the terminal, and gives them to the operating system to perform. To better understand how the shell actually works, you can read  [Médium](https://medium.com/@winfrednginakilonzo/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd)

### <font color=blue>About this project :</font>

This project is a simple version of the linux shell made for Holberton School taking part of the "Low-level programming & Algorithm - Linux and Unix system programming" projects.
It is created using the C programming Language and it can do many functionalities that a real shell does.

### <font color=blue>Requirements:</font>

- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. - It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)

### <font color=blue>Essential Functionalities of the Simple Shell :</font>
- <p>  Displays a prompt "#cisfun$ " and waits for user input.
- Runs all commands of type "executable program" (ls and /bin/ls).<br>
- Runs the following build_in commands: exit, env, setenv and unsetenv.<br>
- Handles commands with arguments.<br>
- Handles the PATH global variable.<br>
- Handles The EOF (End Of File) condition.<br>
- Handles the Ctrl + C signal -> It doesn't exit the shell

### <font color=blue>Files description :</font>

 <font color=green>**1. AUTHORS :</font>** <p> This file lists all individuals having contributed content to the repository
<p>GuerinTifenn <8807@holbertonstudents.com><br>
Francianeny <8877@holbertonstudents.com></p>

 <font color=green>2. **man_1_simple_shell : </font>**  <p>Manual page for the simple_shell

<font color=green>3. **shell.h :</font>** <p>Header file

<font color=green>4. **environnement.c :</font>**
- <p>_getenv -> Get the value of an environment variable<br>
- _strncmp -> Takes as parameters the two strings to compare<br>
 - print_environment -> Print the environment variables<br>
- _strdup -> Copy a string and returns pointer to a allocated space in memory

<font color=green>5. **execute.c :</font>**
- <p>tokenize_input -> Tokenize the input command<br>
- execute_command -> Execute the given command<br>
- find_and_execute_command -> Find and execute the command<br>
- _sprintf -> write formatted data into a string<br>
- execute_command_with_path -> Execute the command with the specified path

<font color=green>6. **main.c :</font>**
<p>The main entry point for the example.


### <font color=blue>List of allowed functions and system calls+ :</font>

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

### <font color=blue>Usage :</font>

You can try your shell by following these steps:

<font color=green>-  ***step 1 :</font>*** <p> Clone our repository using this command, (you need to have git installed on your machine first)

> git clone https://github.com/Francianeny/simple_shell


<font color=green>-  ***step 2 :</font>*** <p> Change directory to simple_shell:

> cd simple_shell

<font color=green>- ***Step 3 :</font>*** <p>Compile the C files in this way:

> gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

<font color=green>- ***Step 4 :</font>***  <p>Run the shell:

> ./hsh

<font color=green>- ***Step 5 :</font>*** <p>*Interactive mode* :
> ![alt text](<int mode.png>)<p>*Non-interactive mode* :
(à vérifier, erreur de compilation à la fin)


<font color=green>**Exiting the shell :</font>** <p>When you want to exit the shell, you can use one of the following methods:

1. Type the command "exit"

> exit

2. Press on Ctrl + D

> ![alt text](<Capture d'écran 2024-04-23 150337.png>)

### <font color=green>Target output :</font>
* Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
* The only difference is when you print an error, the name of the program must be equivalent to your argv[0]

Example of error with sh:

> ![alt text](<message d'erreur.png>)

### <font color=blue>Flowchart :</font>
<p>It's a tool that us individuals visualize a process in discrete steps organized in a sequence of events.

It can be used to represent our workflows.

> ![alt text](<Flowchart Simple Shell.png>)



































