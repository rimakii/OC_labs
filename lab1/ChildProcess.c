#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char filename[100];
    char numbers[256];

    if (read(STDIN_FILENO, filename, sizeof(filename)) < 0) {
        perror("Child read filename");
        exit(EXIT_FAILURE);
    }

    if (read(STDIN_FILENO, numbers, sizeof(numbers)) < 0) {
        perror("Child read numbers");
        exit(EXIT_FAILURE);
    }

    int sum = 0, num;
    char *token = strtok(numbers, " ");
    while (token != NULL) {
        num = atoi(token);
        sum += num;
        token = strtok(NULL, " ");
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Sum: %d\n", sum);
    fclose(file);

    exit(EXIT_SUCCESS);
}