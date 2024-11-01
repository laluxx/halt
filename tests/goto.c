#include <stdio.h>

int main() {
    int i = 0;
    infinite_loop:
    printf("Goto: %i\n", i);
    i++;
    goto infinite_loop;
    
    return 0;
}

