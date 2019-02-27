#include "lib/binary_search.h"
#include "lib/consecutive_sums.h"
#include "lib/rpn_calc.h"

#include <stdio.h>

int main() {
    binary_search_test();
    consecutive_sums_test();
    rpn_calc_test();
    printf("tests all passed, good stuff :)\n");
    return 0;
}
