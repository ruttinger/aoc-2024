#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    const char *pattern = "mul\\(([0-9]+),[ ]*([0-9]+)\\)";
    regex_t regex;
    regmatch_t matches[3];
    char line[256];
    int result = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        regfree(&regex);
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        char *ptr = line;
        while (regexec(&regex, ptr, 3, matches, 0) == 0) {
            char num1_str[16], num2_str[16];
            int num1, num2;

            snprintf(num1_str, matches[1].rm_eo - matches[1].rm_so + 1, "%s", ptr + matches[1].rm_so);
            snprintf(num2_str, matches[2].rm_eo - matches[2].rm_so + 1, "%s", ptr + matches[2].rm_so);

            num1 = atoi(num1_str);
            num2 = atoi(num2_str);

            result += num1 * num2;

            ptr += matches[0].rm_eo;
        }
    }

    fclose(file);
    regfree(&regex);

    // Print the result
    printf("result: %d\n", result);

    return 0;
}
