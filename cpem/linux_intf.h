#ifndef _LINUX_H
#define _LINUX_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>

extern uint8 pgSize;
char orig_command_line[256];

void nix_setpage() {
    struct winsize w;
    
    // Use ioctl to get window size
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
    } else {
        pgSize = w.ws_row-1;
    }
}

char **nix_args() {
    // Allocate space for argument pointers
    size_t arg_count = 0;
    char **argv = malloc(10 * sizeof(char *));  // Initial size for 10 arguments
    char *arg;

    // Split the string by spaces
    arg = strtok(orig_command_line, " ");
    while (arg != NULL) {
        argv[arg_count++] = strdup(arg);  // Store each argument
        if (arg_count % 10 == 0) {  // Resize if needed
            argv = realloc(argv, (arg_count + 10) * sizeof(char *));
        }
        arg = strtok(NULL, " ");
    }

    // If there are no commands, then just run "bash"
    if (!arg_count) {
        argv[arg_count++] = strdup("bash");
    }

    argv[arg_count] = NULL;  // Null-terminate the argument list
    orig_command_line[0] = '\0';
    return argv;
}

int nix_exec() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {     // Child process
        char **args = nix_args();

        // CD to the directory CP/M was working in...
        uint8 dFolder = cDrive + 'A';
        uint8 uFolder = toupper(tohex(userCode));
        uint8 path[4] = { dFolder, FOLDERCHAR, uFolder, 0 };
        uint8 fullpath[128] = FILEBASE;
        strcat((char*)fullpath, (char*)path);
        chdir((const char *)fullpath);

        // Replace the current process with the new one
        _console_reset();
        execvp(args[0], args);

        // If execvp fails
        perror("execvp failed");
        // Free allocated memory
        for (int i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);
        exit(-1);
    } else {            // Parent process
        // Wait for the child to complete
        wait(NULL);
        _console_reinit();
    }
    return 0;
}

void nix_machine(char* mtype) {
    char buffer[128];
    FILE *fp;

    // Execute the command and open a pipe to read the output
    fp = popen("uname -m", "r");
    if (fp == NULL) {
        perror("popen failed");
        strcpy(mtype, "unknown");
        return;
    }

    // Read the output and store it in the result string
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Remove the newline character from the output
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(mtype, buffer, 10);
    }

    // Close the pipe
    pclose(fp);
}

#endif