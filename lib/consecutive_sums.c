#include "consecutive_sums.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct consec_sum_generator {
    const int n;
    const int k_max;
    int k;
};
typedef struct consec_sum_generator generator_t;

generator_t* create_sum_generator(const int n) {
    generator_t g = (generator_t){ n, n/2 + 1, 2 };
    generator_t* pg = malloc(sizeof(generator_t));
    memcpy(pg, &g, sizeof(generator_t));
    return pg;
}

void destroy_sum_generator(struct consec_sum_generator* g) {
    free(g);
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
