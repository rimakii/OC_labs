#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; 

    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        close(pipefd[1]); // Close the write end of pipe

        // Redirect pipe's read end to stdin
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execl("./ChildProcess", "ChildProcess", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else { 
        close(pipefd[0]); // Close the read end of pipe (parent to child)

        char filename[100];
        printf("Enter the filename: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = 0;
        write(pipefd[1], filename, strlen(filename) + 1);

        char numbers[256];
        printf("Enter numbers separated by spaces: ");
        fgets(numbers, sizeof(numbers), stdin);
        write(pipefd[1], numbers, strlen(numbers) + 1);

        // Close the write end of pipe
        close(pipefd[1]);

        wait(NULL);
    }

    return 0;
}