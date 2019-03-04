#include "mental_rng.h"
#include <assert.h>
#include <stdlib.h>

typedef struct mental_rng {
    int value;
} mental_rng_t;

mental_rng_t* create_mental_rng(const int seed) {
    assert(seed < 59 && seed > 0);
    mental_rng_t* r = malloc(sizeof(mental_rng_t));
    r->value = seed;
    return r;
}
void destroy_mental_rng(mental_rng_t* rng) {
    free(rng);
}

int get_rand(mental_rng_t* rng) {
    const int tens = rng->value / 10;
    const int ones = rng->value % 10;
    rng->value = tens + 6 * ones;
    return ones;
}
