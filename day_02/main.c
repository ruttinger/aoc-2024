#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_REPORT_SIZE 8
#define MAX_LINES 1000

void printReport(const int *report) {
    printf("Report: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", report[i]);
    };
    printf("\n");
}

bool problemDampener(const int *report) {
    bool isSafe = true;
    bool trend = 0;
    
    // generate indices
    int indices[8][7];
    for (int skip = 0; skip < 8; skip++) {
        int idx = 0;
        for (int i = 0; i < 8; i++) {
            if (i != skip) {
                indices[skip][idx++] = i;
                // printf("index: %d,%d: %d\n", skip, idx, i);
            }
        }
    }

    for (int i=0; i < 8; i++) {
        isSafe = true;
        for (int j=0; j < 6; j++) {
            int val1 = report[indices[i][j]];
            int val2 = report[indices[i][j+1]];

            // first element (first comparison)
            if (j == 0) {
                trend = val1 - val2 < 0;
            }

            if (abs(val1 - val2) > 3 || val1 - val2 == 0) {
                printf("change of %d\n", abs(val1-val2));
                isSafe = false;
            }
            if ((val1 - val2 < 0) != trend) {
                printf("wrong trend");
                isSafe = false;
            }
        }
        if (isSafe) {
            printf("removing i: [%d] would work\n", i);
            printReport(report);
            return true;
        }
    }

    return false;
}

bool problemDampenerV2(const int *report, int reportSize) {
    bool isSafe = true;
    bool trend = 0;

    // Generate indices that skip one element at a time for the report of varying size
    int indices[MAX_REPORT_SIZE][MAX_REPORT_SIZE - 1];
    for (int skip = 0; skip < reportSize; skip++) {
        int idx = 0;
        for (int i = 0; i < reportSize; i++) {
            if (i != skip) {
                indices[skip][idx++] = i;
            }
        }
    }

    // Check the safety of the report by comparing the skipped values
    for (int i = 0; i < reportSize; i++) {
        isSafe = true;
        for (int j = 0; j < reportSize - 2; j++) { // Compare pairs of values
            int index = indices[i][j];
            int next_index = indices[i][j + 1];

            // First element (first comparison)
            if (j == 0) {
                trend = report[index] - report[next_index] < 0;
            }

            if (abs(report[index] - report[next_index]) > 3 || report[next_index] - report[index] == 0) {
                isSafe = false;
            }
            if ((report[index] - report[next_index] < 0) != trend) {
                isSafe = false;
            }
        }
        if (isSafe) {
            return true;
        }
    }
    return false;
}

int main() {
    FILE *file = fopen("example.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    int value;
    char token;

    int report[8];
    bool isSafe = true;
    int count = 0;

    // increasing: 0, decreasing: 1
    bool trend = 0;

    int safeReportCount = 0;

    while (fscanf(file, "%d%c", &value, &token) == 2) {
        report[count] = value;

        if (count == 1) {
            trend = report[count-1] - report[count] < 0;
        }

        if (count > 0) {
            if (abs(report[count-1] - report[count]) > 3 || report[count-1] - report[count] == 0) {
                isSafe = false;
            }
            if ((report[count-1] - report[count] < 0) != trend) {
                isSafe = false;
            }
        }

        if (token == ' ') { // check if space
            count++;
        }
        if (token == '\n') { // check if newline
            int reportSize = count + 1;
            if (isSafe) {
                safeReportCount++;
            } else {
                if (problemDampener(report)) {
                    safeReportCount++;
                }
                if (problemDampenerV2(report, reportSize)) {
                    safeReportCount++;
                }
            }
            memset(report, 0, 8);
            count = 0;
            isSafe = true;
        }

    }
    printf("Total safe reports: %d\n", safeReportCount);

    fclose(file);
    return 0;
}