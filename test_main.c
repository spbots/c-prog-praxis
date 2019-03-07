#include "lib/binary_search.h"
#include "lib/consecutive_sums.h"
#include "lib/mental_rng.h"
#include "lib/rpn_calc.h"
#include "lib/square_digit_chains.h"

#include <stdio.h>

int main() {
    binary_search_test();
    consecutive_sums_test();
    mental_rng_test();
    rpn_calc_test();
    square_digit_chains_test();
    printf("tests all passed, good stuff :)\n");
    return 0;
}
