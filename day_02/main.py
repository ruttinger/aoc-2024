def problem_dampener(report):
    """
    Check if a report is safe, allowing one value to be skipped in comparisons.
    """
    report_size = len(report)
    for skip in range(report_size):
        is_safe = True
        indices = [i for i in range(report_size) if i != skip]
        
        for j in range(len(indices) - 1):
            current = indices[j]
            next_index = indices[j + 1]

            # First comparison determines the trend
            if j == 0:
                trend = report[current] - report[next_index] < 0

            if abs(report[current] - report[next_index]) > 3 or report[next_index] - report[current] == 0:
                is_safe = False

            if (report[current] - report[next_index] < 0) != trend:
                is_safe = False

        if is_safe:
            return True
    return False


def main():
    """
    Reads a file with varying report sizes and calculates the number of safe reports.
    """
    input_file = "input.txt"
    safe_report_count = 0

    try:
        with open(input_file, "r") as file:
            for line in file:
                # Parse each line into a list of integers
                report = list(map(int, line.split()))

                # Check if the report is safe
                if problem_dampener(report):
                    safe_report_count += 1

    except FileNotFoundError:
        print(f"File {input_file} not found.")
        return

    print(f"Total safe reports: {safe_report_count}")


if __name__ == "__main__":
    main()
