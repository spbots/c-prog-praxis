#include "../lib/rpn_calc.h"
#include <assert.h>
#include <math.h>

void rpn_calc_test() {
    assert(rpn_calc("1 1 +") == 2);
    assert(rpn_calc("1 +1 -1 - +") == 3); // handle unary operators
    assert(rpn_calc("1 1 1 1 1 1 1 1 + + + + + + +") == 8);
    assert(rpn_calc("15 7 1 1 + - / 3 * 2 1 1 + + -") == 5);
    assert(fabs(rpn_calc("19 2.14 + 4.5 2 4.3 / - *") - 85.2974) < 1e-4);
}
