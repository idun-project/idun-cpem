#ifndef _LINUX_H
#define _LINUX_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

char **nix_args(const char *input, size_t len) {
    // Allocate space for argument pointers
    size_t arg_count = 0;
    char **argv = malloc(10 * sizeof(char *));  // Initial size for 10 arguments
    char *arg;
    char *input_copy = strndup(input, len);  // Make a mutable copy of the input string

    // Convert it to lower case
    for (int i = 0; input_copy[i]; i++) {
        input_copy[i] = tolower((unsigned char)input_copy[i]);
    }

    // Split the string by spaces
    arg = strtok(input_copy, " ");
    while (arg != NULL) {
        argv[arg_count++] = strdup(arg);  // Store each argument
        if (arg_count % 10 == 0) {  // Resize if needed
            argv = realloc(argv, (arg_count + 10) * sizeof(char *));
        }
        arg = strtok(NULL, " ");
    }
    argv[arg_count] = NULL;  // Null-terminate the argument list

    free(input_copy);
    return argv;
}

int nix_exec(const char *cmd, size_t length) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {     // Child process
        char **args = nix_args(cmd, length);

        // Replace the current process with the new one
        execvp(args[0], args);

        // If execvp fails
        perror("execvp failed");
        // Free allocated memory
        for (int i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);
        return -1;
    } else {            // Parent process
        // Wait for the child to complete
        wait(NULL);
    }
    return 0;
}
#endif