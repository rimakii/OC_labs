#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

#define SHARED_FILE "/tmp/shared_memory"
#define SHARED_SIZE 1024

void signal_handler(int sig) {}

int main() {
    signal(SIGUSR1, signal_handler);

    int fd = open(SHARED_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Child: open");
        exit(EXIT_FAILURE);
    }

    char *shared_memory = mmap(NULL, SHARED_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("Child: mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    pause();

    char filename[100];
    char numbers[256];

    sscanf(shared_memory, "%s\n%[^\n]", filename, numbers);

    int sum = 0, num;
    char *token = strtok(numbers, " ");
    while (token != NULL) {
        num = atoi(token);
        sum += num;
        token = strtok(NULL, " ");
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Child: fopen");
        munmap(shared_memory, SHARED_SIZE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Sum: %d\n", sum);
    fclose(file);

    munmap(shared_memory, SHARED_SIZE);
    close(fd);

    kill(getppid(), SIGUSR2);

    return 0;
}