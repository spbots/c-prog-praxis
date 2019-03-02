#include "consecutive_sums.h"

#include <assert.h>

struct consec_sum_generator {
    const int n;
    const int k_max;
    int k;
};
typedef struct consec_sum_generator generator_t;

generator_t create_sum_generator(const int n) {
    return (generator_t){ n, n/2 + 1, 2 };
}

sum_numbers_t get_next(generator_t* g) {
    assert(g);
    int k = 0;
    int sum_start = 0;

    for (; g->k <= g->k_max && sum_start == 0; g->k++) {
        k = g->k;
        const int n_div_k = g->n / k;
        const int n_mod_k = g->n % k;
        const int k_div_2 = k / 2;
        const int is_even = k % 2 == 0;

        if (is_even && (k/2 == n_mod_k)) {
            sum_start = n_div_k - k_div_2 + 1;
        } else if (!is_even && (n_mod_k == 0)) {
            sum_start = n_div_k - k_div_2;
        }
    }

    const int is_valid = sum_start > 0;
    return (sum_numbers_t) {
        .sum_start = is_valid ? sum_start : 0,
        .consecutive_numbers =  is_valid ? k : 0 };
}

static int is_eq(const sum_numbers_t in, const int start, const int num) {
    return in.sum_start == start && in.consecutive_numbers == num;
}
void consecutive_sums_test() {
    {
        generator_t g = create_sum_generator(0);
        assert(is_eq(get_next(&g), 0, 0));
    }{
        generator_t g = create_sum_generator(2);
        assert(is_eq(get_next(&g), 0, 0));
    }{
        generator_t g = create_sum_generator(3);
        assert(is_eq(get_next(&g), 1, 2));
        assert(is_eq(get_next(&g), 0, 0));
    }{
        generator_t g = create_sum_generator(15);
        assert(is_eq(get_next(&g), 7, 2));
        assert(is_eq(get_next(&g), 4, 3));
        assert(is_eq(get_next(&g), 1, 5));
        assert(is_eq(get_next(&g), 0, 0));
    }{
        generator_t g = create_sum_generator(21);
        assert(is_eq(get_next(&g), 10, 2));
        assert(is_eq(get_next(&g), 6, 3));
        assert(is_eq(get_next(&g), 1, 6));
        assert(is_eq(get_next(&g), 0, 0));
    }
}
