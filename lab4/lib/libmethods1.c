#include <math.h>
#include "../include/methods.h"

float SinIntegral(float A, float B, float e) {
    float result = 0.0f;
    for (float x = A; x < B; x += e) {
        result += sinf(x) * e;
    }
    return result;
}

int* Sort(int* array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return array;
}
