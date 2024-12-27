#include <stdio.h>
#include <dlfcn.h>
#include <math.h>


typedef float (*SinIntegralFunc)(float, float, float);
typedef int* (*SortFunc)(int*, int);

int main() {
    char* libs[] = {"./libmethods1.so", "./libmethods2.so"};
    int current_lib = 0;
    void* handle = dlopen(libs[current_lib], RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }

    SinIntegralFunc SinIntegral = (SinIntegralFunc)dlsym(handle, "SinIntegral");
    SortFunc Sort = (SortFunc)dlsym(handle, "Sort");

    if (!SinIntegral || !Sort) {
        fprintf(stderr, "Error finding symbols: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    int choice;
    while (1) {
        printf("0 - Switch library, 1 - SinIntegral, 2 - Sort, -1 - Exit\n");
        scanf("%d", &choice);

        if (choice == -1) break;
        if (choice == 0) {
            dlclose(handle);
            current_lib = 1 - current_lib;
            handle = dlopen(libs[current_lib], RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "Error loading library: %s\n", dlerror());
                return 1;
            }
            SinIntegral = (SinIntegralFunc)dlsym(handle, "SinIntegral");
            Sort = (SortFunc)dlsym(handle, "Sort");
        } else if (choice == 1) {
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
    }

    dlclose(handle);
    return 0;
}
