#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#define SHARED_FILE "/tmp/shared_memory"
#define SHARED_SIZE 1024

volatile sig_atomic_t child_ready = 0;

void signal_handler(int sig) {
    if (sig == SIGUSR2) {
        child_ready = 1;
    }
}

int main() {
    signal(SIGUSR2, signal_handler);

    int fd = open(SHARED_FILE, O_CREAT | O_RDWR, 0600);
    if (fd == -1) {
        perror("Parent: open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd, SHARED_SIZE) == -1) {
        perror("Parent: ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char *shared_memory = mmap(NULL, SHARED_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("Parent: mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        munmap(shared_memory, SHARED_SIZE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execl("./ChildProcess_exe", "./ChildProcess_exe", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        char filename[100];
        printf("Enter the filename: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = 0;

        char numbers[256];
        printf("Enter numbers separated by spaces: ");
        fgets(numbers, sizeof(numbers), stdin);

        snprintf(shared_memory, SHARED_SIZE, "%s\n%s", filename, numbers);

        kill(pid, SIGUSR1);

        while (!child_ready) {
            pause();
        }

        printf("Child process completed. Check the file: %s\n", filename);

        munmap(shared_memory, SHARED_SIZE);
        close(fd);
        unlink(SHARED_FILE);
        wait(NULL);
    }

    return 0;
}