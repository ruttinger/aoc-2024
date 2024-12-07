import copy
import sys

def traverse(grid):
    is_cycle = False
    def check_cycle(x, y, direction):
        match(direction):
            case '>':
                # check if going right results in cycle
                if y < len(grid) -1 and grid[x][y+1] == "R":
                    return True
            case '<':
                # check if going left results in cycle
                if y > 0 and grid[x][y-1] == "L":
                    return True
            case '^':
                # check if going up results in cycle
                if x > 0 and grid[x-1][y] == "U":
                    return True
            case 'v':
                # check if going down results in cycle
                if x < len(grid[x]) -1 and grid[x+1][y] == "D":
                    return True


    def move_guard(x, y, direction):
        is_cycle = False
        direction_map = {'^': 'U', 'v': 'D', '>': 'R', '<': 'L'}
        grid[x][y] = direction_map.get(direction, '')
        if direction == '>':  # Move right
            if y < len(grid[x]) - 1:
                if grid[x][y + 1] == "#" and x < len(grid) - 1:
                    grid[x + 1][y] = 'v'  # Go down
                    is_cycle = check_cycle(x+1, y, 'v')
                else:
                    grid[x][y + 1] = '>'
                    is_cycle = check_cycle(x, y+1, '>')
                return (True, is_cycle)
        elif direction == '<':  # Move left
            if y > 0:
                if grid[x][y - 1] == "#" and x > 0:
                    grid[x - 1][y] = '^'  # Go up
                    is_cycle = check_cycle(x-1, y, '^')
                else:
                    grid[x][y - 1] = '<'
                    is_cycle = check_cycle(x, y-1, '<')
                return (True, is_cycle)
        elif direction == '^':  # Move up
            if x > 0:
                if grid[x - 1][y] == "#" and y < len(grid[x]) - 1:
                    grid[x][y + 1] = '>'  # Go right
                    is_cycle = check_cycle(x, y+1, '>')
                else:
                    grid[x - 1][y] = '^'
                    is_cycle = check_cycle(x-1, y, '^')
                return (True, is_cycle)
        elif direction == 'v':  # Move down
            if x < len(grid) - 1:
                if grid[x + 1][y] == "#" and y > 0:
                    grid[x][y - 1] = '<'  # Go left
                    is_cycle = check_cycle(x, y-1, '<')
                else:
                    grid[x + 1][y] = 'v'
                    is_cycle = check_cycle(x+1, y, 'v')
                return (True, is_cycle)
        return (False, is_cycle)

    while True:
        still_here = False
        is_cycle = False
        for x, row in enumerate(grid):
            for y, cell in enumerate(row):
                if cell in ('>', '<', '^', 'v'):
                    still_here, is_cycle = move_guard(x, y, cell)
                    break
        if not still_here:
            # print("finished")
            # positions_visited = sum(cell in ('U', 'D', 'R', 'L') for row in grid for cell in row)
            # print(positions_visited)
            # print(grid)
            return False
        if is_cycle:
            return True

def main(input):
    file_name = input + ".txt"

    if input == "input":
        width = 130
        height = 130
    elif input == "example":
        width = 10
        height = 10

    x = 0
    y = 0
    grid = [[0 for w in range(width)] for h in range(height)] 

    with open(file_name, "r") as file:
        for line in file:
            for char in line:
                if (char == '\n' or y >= width or x >= height):
                    continue
                grid[x][y] = char
                y += 1
            y = 0
            x += 1
    count = 0

    for x, row in enumerate(grid):
        for y, cell in enumerate(row):
            print(x, y)
            if cell not in ('#', '<', '>', 'v', '^'):
                temp = grid[x][y]
                grid[x][y] = '#'
                is_cycle = traverse(copy.deepcopy(grid))
                if is_cycle:
                    count += 1
                grid[x][y] = temp
    print(count)
if __name__ == "__main__":
    input = sys.argv[1]
    main(input)
