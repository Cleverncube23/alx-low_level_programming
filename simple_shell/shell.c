#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main()
{
    char command[MAX_COMMAND_LENGTH];
    char *args[2] = {NULL, NULL}; // We'll only have one argument (the command)

    while (1)
    {
        printf("simple_shell$ "); // Display the prompt
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            // Handle the end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Check if the user typed "exit" to quit the shell
        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        // Fork a new process to execute the command
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process: execute the command
            args[0] = command;
            execve(args[0], args, environ);

            // If execve fails, print an error message and exit
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process: wait for the child to finish
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
