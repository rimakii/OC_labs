#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "include/MedianFilter.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <rows> <cols> <window_size> <iterations> <max_threads>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int window_size = atoi(argv[3]);
    int iterations = atoi(argv[4]);
    int max_threads = atoi(argv[5]);

    if (max_threads > MAX_THREADS) {
        printf("Maximum number of threads is %d\n", MAX_THREADS);
        return 1;
    }

    int **matrix = (int **)malloc(rows * sizeof(int *));
    int **result = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        result[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 256;
        }
    }

    printf("Original Matrix:\n");
    print_matrix(matrix, rows, cols);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t threads[max_threads];
    ThreadData thread_data[max_threads];

    for (int i = 0; i < max_threads; i++) {
        thread_data[i].matrix = matrix;
        thread_data[i].result = result;
        thread_data[i].rows = rows;
        thread_data[i].cols = cols;
        thread_data[i].window_size = window_size;
        thread_data[i].iterations = iterations;
        thread_data[i].thread_id = i;
        thread_data[i].max_threads = max_threads;
        pthread_create(&threads[i], NULL, thread_function, &thread_data[i]);
    }

    for (int i = 0; i < max_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time taken: %f seconds\n", time_taken);

    printf("\nFiltered Matrix:\n");
    print_matrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
        free(result[i]);
    }
    free(matrix);
    free(result);

    return 0;
}