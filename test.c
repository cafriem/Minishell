#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline.h>

int main() {
    while (1) {
        char input[256];
        printf("Minishell> ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // Remove the newline character
		printf("start = %s\n", readline("Minishell> "));
        if (strcmp(input, "./a.out") == 0) {
            // Handle running ./a.out
            int child_pid = fork();
            if (child_pid == 0) {
                // This is the child process
                char *args[] = {"./a.out", NULL};
                execve("./a.out", args, NULL);
                // If execve fails, handle the error here
                perror("execve");
                exit(1);
            } else if (child_pid < 0) {
                // Handle fork error
                perror("fork");
            } else {
                // This is the parent process
                int status;
                waitpid(child_pid, &status, 0);
                // You can optionally check the exit status of the child process
                if (WIFEXITED(status)) {
                    int exit_status = WEXITSTATUS(status);
                    printf("./a.out exited with status %d\n", exit_status);
                }
            }
        } else {
            // Handle other commands
            // Implement your command processing logic here
            // ...
        }
    }
    return 0;
}
