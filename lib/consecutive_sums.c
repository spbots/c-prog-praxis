#include "consecutive_sums.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

SumNumbersArray consecutive_sums(const int n)
{
    const int k_max = n/2 + 1;

    // todo: what is the actual upper limit needed for alloc?
    SumNumbers* arr = calloc(k_max, sizeof(SumNumbers));
    int size = 0;

    for (int k = 2; k <= k_max; ++k) {
        const int n_div_k = n / k;
        const int n_mod_k = n % k;
        const int k_div_2 = k / 2;
        const int is_even = k % 2 == 0;

        if (is_even && (k/2 == n_mod_k)) {
            const int sum_start = n_div_k - k_div_2 + 1;
            if (sum_start <= 0) break;

            arr[size++] = (SumNumbers){
                .sum_start = sum_start,
                .consecutive_numbers = k
            };
        } else if (!is_even && (n_mod_k == 0)) {
            const int sum_start = n_div_k - k_div_2;
            if (sum_start <= 0) break;

            arr[size++] = (SumNumbers){
                .sum_start = sum_start,
                .consecutive_numbers = k
            };
        }
    }

    return (SumNumbersArray){
        .a = arr,
        .size = size
    };
}


static int is_eq(const SumNumbers in, const int start, const int num) {
    return in.sum_start == start && in.consecutive_numbers == num;
}
void consecutive_sums_test() {
    {
        SumNumbersArray out = consecutive_sums(0);
        assert(out.size == 0);
        free(out.a);
    }{
        SumNumbersArray out = consecutive_sums(2);
        assert(out.size == 0);
        free(out.a);
    }{
        SumNumbersArray out = consecutive_sums(3);
        assert(out.size == 1);
        assert(is_eq(out.a[0], 1, 2));
        free(out.a);
    }{
        SumNumbersArray out = consecutive_sums(15);
        assert(out.size == 3);
        assert(is_eq(out.a[0], 7, 2));
        assert(is_eq(out.a[1], 4, 3));
        assert(is_eq(out.a[2], 1, 5));
        free(out.a);
    }{
        SumNumbersArray out = consecutive_sums(21);
        assert(out.size == 3);
        assert(is_eq(out.a[0], 10, 2));
        assert(is_eq(out.a[1], 6, 3));
        assert(is_eq(out.a[2], 1, 6));
        free(out.a);
    }
}
