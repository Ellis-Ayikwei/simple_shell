#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    while (1) {
        display_prompt();

        char** command = read_command();

        if (command == NULL || command[0] == NULL) {
            printf("\n");
            break;
        }

        execute_command(command);

        for (int i = 0; command[i] != NULL; i++) {
            free(command[i]);
        }
        free(command);
    }

    return 0;
}

