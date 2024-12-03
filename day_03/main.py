import re

def main():
    pattern = r"mul\(([0-9]+),[ ]*([0-9]+)\)|do\(\)|don't\(\)"
    result = 0
    mul_enabled = True

    with open("input.txt", "r") as file:
        for line in file:
            operations = re.finditer(pattern, line)
            for operation in operations:
                match = operation.group(0)
                if match.startswith("mul"):
                    if mul_enabled:
                        factors = re.match(r"mul\(([0-9]+),[ ]*([0-9]+)\)", match)
                        if factors:
                            num1 = int(factors.group(1))
                            num2 = int(factors.group(2))
                            result += num1 * num2
                elif match == "do()":
                    mul_enabled = True
                elif match == "don't()":
                    mul_enabled = False

    print("result:", result)

if __name__ == "__main__":
    main()
