#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 1000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int timesInArray(int *array, int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            count++;
        }
    }
    return count;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int firstNumbers[MAX_LINES];
    int secondNumbers[MAX_LINES];
    int lowestFirst = 0;
    int lowestSecond = 0;
    int count = 0;

    while (fscanf(file, "%d %d", &firstNumbers[count], &secondNumbers[count]) == 2) {
        count++;
        if (count >= MAX_LINES) {
            printf("Reached maximum array size of %d\n", MAX_LINES);
            break;
        }
    }

    fclose(file);

    qsort(firstNumbers, count, sizeof(int), compare);
    qsort(secondNumbers, count, sizeof(int), compare);

    int minCount = count;

    int totalDistance = 0;

    int totalSimilarity = 0;

    printf("Distances between elements in the two arrays:\n");
    for (int i = 0; i < minCount; i++) {
        int distance = abs(firstNumbers[i] - secondNumbers[i]);
        totalDistance += distance;
        
        int similarity = firstNumbers[i] * timesInArray(secondNumbers, MAX_LINES, firstNumbers[i]);
        totalSimilarity += similarity;
    }

    printf("\nTotal distance: %d\n", totalDistance);

    printf("\nTotal similarity: %d\n", totalSimilarity);

    return 0;
}
