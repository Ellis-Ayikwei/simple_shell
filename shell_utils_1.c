// shell_utils.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100

void display_prompt() {
    printf("$ ");
    fflush(stdout);
}

char** read_command() {
    char input[MAX_INPUT_LENGTH];
    fgets(input, sizeof(input), stdin);

    // Remove the newline character at the end
    input[strcspn(input, "\n")] = '\0';

    // Tokenize the input into command and arguments
    char** tokens = malloc(sizeof(char*) * (MAX_INPUT_LENGTH / 2 + 1));
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    char* token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        tokens[i] = strdup(token);
        if (tokens[i] == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL; // Null-terminate the array

    return tokens;
}

void execute_command(char** command) {
    // Check if the command is "exit" (built-in)
    if (strcmp(command[0], "exit") == 0) {
        // Free allocated memory before exiting
        for (int i = 0; command[i] != NULL; i++) {
            free(command[i]);
        }
        free(command);

        // Exit the shell
        exit(EXIT_SUCCESS);
    }

    // Check if the command is "env" (built-in)
    if (strcmp(command[0], "env") == 0) {
        // Print the current environment variables
        char** env = environ;
        while (*env != NULL) {
            printf("%s\n", *env);
            env++;
        }

        // Free allocated memory
        for (int i = 0; command[i] != NULL; i++) {
            free(command[i]);
        }
        free(command);

        return;
    }

    char* path = getenv("PATH");
    char* path_copy = strdup(path);

    if (path_copy == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    char* dir = strtok(path_copy, ":");
    while (dir != NULL) {
        char* full_path = malloc(strlen(dir) + strlen(command[0]) + 2);
        if (full_path == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command[0]);

        struct stat st;
        if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR) {
            // The file exists and is executable
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                if (execv(full_path, command) == -1) {
                    perror("execv");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                int status;
                waitpid(pid, &status, 0);
                free(full_path);
                return;
            }
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    // If we reach here, the command doesn't exist in any directory in the PATH
    printf("Command not found: %s\n", command[0]);

    free(path_copy);
}

