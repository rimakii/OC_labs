#include <math.h>
#include "../include/methods.h"

float SinIntegral(float A, float B, float e) {
    float result = 0.0f;
    for (float x = A; x < B; x += e) {
        result += (sinf(x) + sinf(x + e)) * e / 2;
    }
    return result;
}

int* Sort(int* array, int size) {
    if (size < 2) return array;
    int pivot = array[size / 2];
    int i = 0, j = size - 1;
    while (i <= j) {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;
        if (i <= j) {
            int temp = array[i];
            array[i++] = array[j];
            array[j--] = temp;
        }
    }
    Sort(array, j + 1);
    Sort(array + i, size - i);
    return array;
}
