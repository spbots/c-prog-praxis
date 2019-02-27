#include "lib/rpn_calc.h"

#include <stdio.h>

int main() {
    char input[1024];
    printf(".....calc.....\n");
    while (fgets(input, 1024, stdin)) {
        printf("%lf\n", rpn_calc(input));
    }
    return 0;
}
