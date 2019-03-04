#include "../lib/mental_rng.h"
#include <assert.h>
#include <stdint.h>

/*
regardless of the seed, the distribution of digits stays roughly
the same - digits 9 and 0 show up less frequently, ~8.6% instead
of the expected 10%, since 59 and 60 are unreachable by the
algorithm. The distribution is fairly uniform across 1 to 8.
*/

const uint32_t N_TESTS = 10000;
const int SEED = 45;

#if 0 // toggle to 1 to print distribution test results.
#include <stdio.h>
void dump_results(uint32_t x[10]) {
    for (int i = 0; i < 10; ++i) {
        printf("digit: %d  freq: %f %%\n", i, (100.0 * x[i])/N_TESTS);
    }
}
#else
void dump_results(uint32_t x[10]) {(void)x;}
#endif

static void test_distribution() {
    uint32_t digit_freq[10] = {0};
    struct mental_rng* rng = create_mental_rng(SEED);

    for (uint32_t i = 0; i < N_TESTS; ++i) {
        digit_freq[get_rand(rng)]++;
    }

    dump_results(digit_freq);
    destroy_mental_rng(rng);
}

static void test_correctness() {
    // example sequence: 23 → 20 → 02 → 12 → 13 → 19 → 55 → 35
    struct mental_rng* rng = create_mental_rng(23);
    assert(get_rand(rng) == 3);
    assert(get_rand(rng) == 0);
    assert(get_rand(rng) == 2);
    assert(get_rand(rng) == 2);
    assert(get_rand(rng) == 3);
    assert(get_rand(rng) == 9);
    assert(get_rand(rng) == 5);
    assert(get_rand(rng) == 5);
    destroy_mental_rng(rng);
}

void mental_rng_test() {
    test_distribution();
    test_correctness();
}
