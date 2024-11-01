#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO ~halt test~ should run all the tests
// TODO halt() should take a file, a function, and the input(s)

#define MAX_LINE_LENGTH 1024

bool halt(const char *filename);
bool contains_infinite_loop_pattern(const char *line);

bool halt(const char *filename) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    bool found_pattern = false;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror(filename);
        return false;
    }

    while (fgets(line, sizeof(line), file)) {
        if (contains_infinite_loop_pattern(line)) {
            found_pattern = true;
            break; // No need to continue if we already found a pattern
        }
    }

    fclose(file);
    return found_pattern;
}

bool contains_infinite_loop_pattern(const char *line) {
    // Remove leading and trailing whitespace
    while (isspace((unsigned char)*line)) {
        line++;
    }
    char *end = line + strlen(line) - 1;
    while (end > line && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0'; // Null-terminate the trimmed line

    // Check for simple infinite loop patterns
    if (strstr(line, "while(1)") || strstr(line, "while(true)") ||
        strstr(line, "for(;;)")) {
        return true;
    }

    // Further checks for potential infinite loop patterns
    if (strstr(line, "while") || strstr(line, "for")) {
        // Look for common loop patterns in C
        if (strstr(line, "while (1") || strstr(line, "for (") ||
            strstr(line, "while (true")) {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    bool infinite = halt(argv[1]);
    if (infinite) {
        printf("%s will loop forever\n", argv[1]);
    } else {
        printf("%s will not loop forever\n", argv[1]);
    }

    return 0;
}
