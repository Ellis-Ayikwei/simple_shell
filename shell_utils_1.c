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
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (execvp(command[0], command) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

