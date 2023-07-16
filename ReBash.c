#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    int Command_size = 1024;
    int arg_size = 64;
    char command[Command_size];
    char *arguments[arg_size];
    int status;

    while (1) 
    {
    // ReBash Command-Line Prompt
        printf("ReBash>> ");
    // Get Command from input and strip newline character
        fgets(command, Command_size, stdin);
        command[strcspn(command, "\n")] = '\0';
    // If command== "exit" then exit the ReBash shell
        if (strcmp(command, "exit") == 0) 
        {
            exit(0);
        }
    // Parse command into argument tokens and place into array
        int argc = 0;
        char *token = strtok(command, " ");
        while (token != NULL && argc < arg_size - 1) 
        {
            arguments[argc] = token;
            argc++;
            token = strtok(NULL, " ");
        }
        arguments[argc] = NULL;
    // Fork to make a new child process
        pid_t pid = fork();
    // Error occurred during forking
        if (pid == -1) 
        {
            perror("Forking error");
        } 
        else if (pid == 0) 
        {
            // Child process attempts to run command
            execvp(arguments[0], arguments);
            // If the child proccess fails, the error is printed and child process exits
            perror("Error");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            // Parent process waitss until the child process is complete
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}


