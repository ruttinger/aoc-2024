#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_HEIGHT 130
#define MAX_WIDTH 130

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int modX;
    int modY;
} Modifiers;

char grid[MAX_HEIGHT][MAX_WIDTH];

int visited[MAX_HEIGHT][MAX_WIDTH]; // 0: unvisited, 1-4: direction
int visitedTemp[MAX_HEIGHT][MAX_WIDTH];

Point guardPos = {-1, -1};
char direction;
bool still_here = true;
int cycles = 0;

bool isGuard(char c) {
    return (c == '<' || c == 'v' || c == '^' || c == '>');
}

int charToDir(char c) {
    switch (c) {
        case '<': return 1; // Left
        case 'v': return 2; // Down
        case '>': return 3; // Right
        case '^': return 4; // Up
        default: return 0; // Invalid
    }
}

bool withinBounds(Modifiers modifiers) {
    return (0 <= (guardPos.x + modifiers.modX) && (guardPos.x + modifiers.modX) < MAX_WIDTH) &&
        (0 <= (guardPos.y + modifiers.modY) && (guardPos.y + modifiers.modY) < MAX_HEIGHT);
}

bool isObstruction(Modifiers modifiers) {
    return grid[guardPos.x + modifiers.modX][guardPos.y + modifiers.modY] == '#';
}

bool isCycle() {
    return charToDir(direction) == visitedTemp[guardPos.x][guardPos.y];
}

char turningRight(char direction) {
    switch (direction) {
        case '<':
            return '^';
        case '>':
            return 'v';
        case '^':
            return '>';
        case 'v':
            return '<';
        default:
            break;
    }
    return 0;
}

Modifiers getModifiers() {
    Modifiers modifiers = {0, 0};
    switch(direction) {
        case '<':
            modifiers.modX = 0;
            modifiers.modY = -1;
            break;
        case '>':
            modifiers.modX = 0;
            modifiers.modY = +1;
            break;
        case '^':
            modifiers.modX = -1;
            modifiers.modY = 0;
            break;
        case 'v':
            modifiers.modX = +1;
            modifiers.modY = 0;
            break;
        default:
            break;
    }
    return modifiers;
}

int move(Modifiers modifiers) {
    if (withinBounds(modifiers)) {
        if (!isObstruction(modifiers)) {
            visitedTemp[guardPos.x][guardPos.y] = charToDir(direction);
            guardPos.x += modifiers.modX;
            guardPos.y += modifiers.modY;
        } else {
            direction = turningRight(direction);
        }
    } else {
        still_here = false;
        visitedTemp[guardPos.x][guardPos.y] = charToDir(direction);
        guardPos.x = -1;
        guardPos.y = -1;
    }
    return 0;
}

int traverse() {
    // initial direction
    direction = grid[guardPos.x][guardPos.y];
    while (still_here) {
        if (isGuard(direction)) {
            if (!isCycle()) {
                move(getModifiers());
            } else {
                cycles++;
                return 0;
            }
        } else {
            still_here = false;
        }
    }

    return 0;
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
        if (y < MAX_WIDTH) {
            if (isGuard(c)) {
                grid[x][y] = c;
                guardPos.x = x;
                guardPos.y = y;
            } else if (c == '#') {
                grid[x][y] = c;
            }
            y++;
        } else {
            y = 0;
            x++;
        }   
    }

    Point initialPos = guardPos;

    if (guardPos.x != -1 && guardPos.y != -1) {
        traverse();
    }

    int count = 0;
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            visited[i][j] = visitedTemp[i][j];
            if (visited[i][j] > 0) {
                count++;
            }
        }
    }

    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            if (visited[i][j] > 0) {
                char temp = grid[i][j];
                grid[i][j] = '#';
                guardPos = initialPos;
                still_here = true;
                memset(visitedTemp, 0, sizeof(visitedTemp));
                traverse();
                grid[i][j] = temp;
            }
        }
    }

    printf("count: %d\n", count);
    printf("cycles: %d\n", cycles);

    fclose(file);
    return 0;
}
