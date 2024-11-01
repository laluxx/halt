#include <stdio.h>
#include <stdbool.h>

int main() {
    int i = 0;
    while (true) {
        printf("while(true): %i\n", i);
        i++;
        break;
    }
    return 0;
}
