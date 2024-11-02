#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include <pthread.h>

#define MAX_THREADS 20

typedef struct {
    int **matrix;
    int **result;
    int rows;
    int cols;
    int window_size;
    int iterations;
    int thread_id;
    int max_threads;
} ThreadData;

void apply_median_filter(int **matrix, int **result, int rows, int cols, int window_size);
void *thread_function(void *arg);
void print_matrix(int **matrix, int rows, int cols);

#endif 