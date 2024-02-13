#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array, size, i, sum = 0;

    // Get array size from user
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    // Allocate memory for the array
    if ((array = (int *)malloc(size * sizeof(int))) == NULL) {
        printf("malloc");
        exit(1);
    }

    // Fill the array with values (1 to size)
    for (i = 0; i < size; i++) {
        array[i] = i + 1;
    }

    // Calculate the sum of array elements
    for (i = 0; i < size; i++) {
        sum += array[i];
    }

    // Print the array and its sum
    printf("Array elements: ");
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\nSum: %d\n", sum);

    // Deallocate the memory
    free(array);

    return 0;
}
