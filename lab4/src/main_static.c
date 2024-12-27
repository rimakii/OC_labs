#include <stdio.h>
#include "methods.h"

int main() {
    int choice;
    printf("Choose a function: 1 - SinIntegral, 2 - Sort\n");
    scanf("%d", &choice);

    if (choice == 1) {
        float A, B, e;
        printf("Enter A, B, e: ");
        scanf("%f %f %f", &A, &B, &e);
        printf("Result: %f\n", SinIntegral(A, B, e));
    } else if (choice == 2) {
        int size;
        printf("Enter array size: ");
        scanf("%d", &size);
        int array[size];
        printf("Enter %d elements: ", size);
        for (int i = 0; i < size; ++i) scanf("%d", &array[i]);
        Sort(array, size);
        printf("Sorted array: ");
        for (int i = 0; i < size; ++i) printf("%d ", array[i]);
        printf("\n");
    }

    return 0;
}
