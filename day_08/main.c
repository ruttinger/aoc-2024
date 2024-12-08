#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

#define MAX_SIZE 50

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    char symbol;
    int count;
    Point antennas[MAX_SIZE^2];
} AntennaTypes;

char grid[MAX_SIZE][MAX_SIZE];

int antennaCount = 0;

AntennaTypes antennaTypes[61];

bool withinBounds(Point point) {
    return (0 <= (point.x) && (point.x) < MAX_SIZE) &&
        (0 <= (point.y) && (point.y) < MAX_SIZE);
}

int char_to_index(char c) {
    if (c >= '0' && c <= '9') return c - '0';       // 0-9
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;  // 10-35
    if (c >= 'a' && c <= 'z') return c - 'a' + 36;  //  36-61
    return -1; // Invalid character
}

double calculate_distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

void set_point(Point point) {
    if (withinBounds(point)) {
        if (!grid[point.x][point.y]) {
            grid[point.x][point.y] = '#';
            antennaCount += 1;
        } else if (grid[point.x][point.y] == '#') {
            antennaCount += 1;
        }
    }
}

void extend_line(Point p1, Point p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;

    Point extended1 = {p1.x + (p1.x - p2.x), p1.y + (p1.y - p2.y)};
    Point extended2 = {p2.x + (p2.x - p1.x), p2.y + (p2.y - p1.y)};

    set_point(extended1);
    set_point(extended2);
}

void generate_unique_pairs(Point points[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            extend_line(points[i], points[j]);
        }
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file \n");
        exit(1);
    }

    int x = 0;
    int y = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if(c == '\n') {
            y = 0;
            x++;
        } else {
            if (c != '.') {
                grid[x][y] = c;
                int i = char_to_index(c);
                if (i == -1) {
                    printf("Invalid character: %c\n", c);
                } else if (i >= 0 && i < 61) {  // Valid index check
                    if (antennaTypes[i].count > 0) {
                        int j = antennaTypes[i].count;
                        antennaTypes[i].antennas[j].x = x;
                        antennaTypes[i].antennas[j].y = y;
                        antennaTypes[i].count += 1;
                    } else {
                        int j = antennaTypes[i].count;
                        antennaTypes[i].symbol = c;
                        antennaTypes[i].antennas[j].x = x;
                        antennaTypes[i].antennas[j].y = y;
                        antennaTypes[i].count += 1;
                    }
                }
            }
            y++;
        }
    }

    for (int i = 0; i < 61; i ++) {
        int n = antennaTypes[i].count;
        if (n > 0) {
            generate_unique_pairs(antennaTypes[i].antennas, n);
        }
    }

    // print grid
    int count = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (grid[i][j]) {
                printf("%c", grid[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Antenna count: %d\n", antennaCount);
    printf("\n");

    return 0;
}