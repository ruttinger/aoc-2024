import re

WORD = 'MAS'

def is_within_bounds(x, y, grid):
    return 0 <= x < len(grid) and 0 <= y < len(grid[0])

def main():

    # input: 140x140
    width = 140
    height = 140

    # # example: 10x10
    # width = 10
    # height = 10

    x = 0
    y = 0
    grid = [[0 for w in range(width)] for h in range(height)] 

    with open("input.txt", "r") as file:
        for line in file:
            for char in line:
                if (char == '\n'):
                    continue
                grid[x][y] = char
                y += 1
            y = 0
            x += 1

    # 0: east, 1: northeast, 2: north, 3: northwest, 4: west, 5: southwest, 6: south, 7: southeast

    modifiers = [[0, 1], [-1, 1], [-1, 0], [-1, -1], [0, -1], [1, -1], [1, 0], [1, 1]]
    
    # found = [{'x', 'y', 'dir'}]
    count = 0
    found = False

    found_A = []
    found_Cross = []

    coordsA = ()

    for x in range(len(grid)):
        for y in range(len(grid[0])):
            if grid[x][y] == WORD[0]:
                for mod in modifiers:
                    modX, modY = x, y
                    for i in range(1, len(WORD)):
                        modX += mod[0]
                        modY += mod[1]
                        if is_within_bounds(modX, modY, grid) and grid[modX][modY] == WORD[i]:
                            if WORD[i] == 'A':
                                coordsA = (modX, modY, modifiers.index(mod) % 2)
                            if i == len(WORD) - 1:
                                # count += 1
                                found = True
                                if coordsA not in found_A:
                                    found_A.append(coordsA)
                                else:
                                    if coordsA not in found_Cross:
                                        # with horizontal crosses (not needed)
                                        # flipped_coordsA = (coordsA[0], coordsA[1], coordsA[2] ^ 1)
                                        # if flipped_coordsA not in found_Cross:
                                        #     found_Cross.append(coordsA)
                                        #     count += 1
                                        if coordsA[2] == 1:
                                            found_Cross.append(coordsA)
                                            count += 1
                            continue
                        else:
                            break

                found = False
    print(found_Cross)
    print(count)

if __name__ == "__main__":
    main()
