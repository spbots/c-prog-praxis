#include "square_digit_chains.h"

#include <assert.h>

/*
Approach:
since we know
- the max number (9999999)
- square_sum_digits(9999999) = 567
- all other results must be less than 567

we can make an array of 567 elements and keep track of whether they
end up at 1 or 89. once we've calculated these, test 568 to 9999999
and check which of the 567 sequences they land in.
*/

int square_sum_digits(int x) {
    int result = 0;
    while (x > 0) {
        const int digit = x % 10;
        x /= 10;
        result += (digit * digit);
    }
    return result;
}

void square_digit_chains_test() {
    assert(square_sum_digits(9999999) == 567);

    // don't bother with zero-indexing, just store a
    // dummy value at index 0.
    char seq_endpoint[568] = {0};
    seq_endpoint[1] = 1;
    seq_endpoint[89] = 89;

    for(int i = 2; i <= 567; ++i) {
        int x = square_sum_digits(i);
        while (seq_endpoint[x] == 0) { x = square_sum_digits(x); }
        seq_endpoint[i] = seq_endpoint[x];
    }

    // set the values in seq_endpoint to either
    // 1 or zero so we can just add in the next loop.
    for (int i = 0; i <= 567; ++i) {
        seq_endpoint[i] = seq_endpoint[i] == 89;
    }

    int n_89s = 0;
    for (int i = 1; i <= 9999999; ++i) {
        n_89s += seq_endpoint[square_sum_digits(i)];
    }
    assert(n_89s == 8581146);
}
