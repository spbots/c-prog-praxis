#include "../lib/consecutive_sums.h"

#include <assert.h>

static int is_eq(const sum_numbers_t in, const int start, const int num) {
    return in.sum_start == start && in.consecutive_numbers == num;
}
void consecutive_sums_test() {
    {
        struct consec_sum_generator* g = create_sum_generator(0);
        assert(is_eq(get_next(g), 0, 0));
        destroy_sum_generator(g);
    }{
        struct consec_sum_generator* g = create_sum_generator(2);
        assert(is_eq(get_next(g), 0, 0));
        destroy_sum_generator(g);
    }{
        struct consec_sum_generator* g = create_sum_generator(3);
        assert(is_eq(get_next(g), 1, 2));
        assert(is_eq(get_next(g), 0, 0));
        destroy_sum_generator(g);
    }{
        struct consec_sum_generator* g = create_sum_generator(15);
        assert(is_eq(get_next(g), 7, 2));
        assert(is_eq(get_next(g), 4, 3));
        assert(is_eq(get_next(g), 1, 5));
        assert(is_eq(get_next(g), 0, 0));
        destroy_sum_generator(g);
    }{
        struct consec_sum_generator* g = create_sum_generator(21);
        assert(is_eq(get_next(g), 10, 2));
        assert(is_eq(get_next(g), 6, 3));
        assert(is_eq(get_next(g), 1, 6));
        assert(is_eq(get_next(g), 0, 0));
        destroy_sum_generator(g);
    }
}
