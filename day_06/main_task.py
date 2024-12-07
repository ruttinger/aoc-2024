import copy
import sys

def traverse(grid):
    # Your existing traversal function
    is_cycle = False
    def check_cycle(x, y, direction):
        match(direction):
            case '>':
                if y < len(grid) -1 and grid[x][y+1] == "R":
                    return True
            case '<':
                if y > 0 and grid[x][y-1] == "L":
                    return True
            case '^':
                if x > 0 and grid[x-1][y] == "U":
                    return True
            case 'v':
                if x < len(grid[x]) -1 and grid[x+1][y] == "D":
                    return True

    def move_guard(x, y, direction):
        # Your existing move guard logic
        ...

    while True:
        still_here = False
        is_cycle = False
        for x, row in enumerate(grid):
            for y, cell in enumerate(row):
                if cell in ('>', '<', '^', 'v'):
                    still_here, is_cycle = move_guard(x, y, cell)
                    break
        if not still_here:
            return False
        if is_cycle:
            return True

def process_grid_chunk(grid_chunk, input_file):
    with open(input_file, "r") as file:
        x, y = 0, 0
        for line in file:
            if x in grid_chunk:
                for char in line:
                    if y < len(grid_chunk[x]):
                        grid_chunk[x][y] = char
                        y += 1
                y = 0
            x += 1

    count = 0
    for x, row in enumerate(grid_chunk):
        for y, cell in enumerate(row):
            if cell not in ('#', '<', '>', 'v', '^'):
                temp = grid_chunk[x][y]
                grid_chunk[x][y] = '#'
                is_cycle = traverse(copy.deepcopy(grid_chunk))
                if is_cycle:
                    count += 1
                grid_chunk[x][y] = temp
    return count

def main(input):
    file_name = input + ".txt"
    grid = [[0 for w in range(130)] for h in range(130)]  # Initialize grid (130x130)

    # Handle input for chunk processing (each chunk corresponds to a row or set of rows)
    grid_chunk = sys.argv[2]  # Argument for chunk (row or range)

    # Process this chunk of the grid
    result = process_grid_chunk(grid_chunk, file_name)
    print(f"Cycle count for this chunk: {result}")

if __name__ == "__main__":
    input = sys.argv[1]
    main(input)
