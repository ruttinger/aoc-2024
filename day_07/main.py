from math import log10

def ints(line):
    return list(map(int, line.strip().split()))

fmt_dict = { "cast_type": ints }

def digits(n):
    return int(log10(n)) + 1

def endswith(a, b):
    return (a - b) % 10 ** digits(b) == 0

def is_tractable(test_value, numbers, check_concat=True):
    *head, n = numbers
    if not head:
        return n == test_value
    q, r = divmod(test_value, n)
    if r == 0 and is_tractable(q, head, check_concat):
        return True
    if check_concat and endswith(test_value, n) and is_tractable(test_value // (10 ** digits(n)), head, check_concat):
        return True
    return is_tractable(test_value - n, head, check_concat)

def solve(data):
    ans1 = ans2 = 0
    for line in data:
        test_value, *numbers = line
        if is_tractable(test_value, numbers, False):
            ans1 += test_value
            ans2 += test_value
        elif is_tractable(test_value, numbers):
            ans2 += test_value
    return ans1, ans2

def main():
    data = []
    with open('input.txt', 'r') as file:
        for line in file:
            test_value, numbers = line.strip().split(':')
            test_value = int(test_value)
            numbers = list(map(int, numbers.split()))
            data.append((test_value, *numbers))
    print(solve(data))
if __name__ == "__main__":
    main()