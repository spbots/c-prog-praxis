#include "rpn_calc.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

enum operator_t {
    op_add, op_sub, op_mul, op_div, op_invalid
};

enum operator_t to_operator(const char* str) {
    switch (str[0]) {
        case '/': return op_div;
        case '*': return op_mul;
        case '+': return strlen(str) == 1 ? op_add : op_invalid;
        case '-': return strlen(str) == 1 ? op_sub : op_invalid;
        default: return op_invalid;
    }
}

double rpn_calc(const char* str){
    const double kFailed = 0.0; // ? better failure case ?? nan?
    if (!(str && *str)) return kFailed;

    size_t size = strlen(str);

    // seems reasonable. there are n-1 operators and a bunch of spaces.
    double* stack_mem = calloc(size/2, sizeof(double));

    // push: *stack++       pop:  *--stack
    double* stack = stack_mem;

    char* str_copy = malloc(size + 1);
    strcpy(str_copy, str);

    // !! not threadsafe !! strtok mutates static variable
    for (char* token = strtok(str_copy, " \n"); token; token = strtok(NULL, " \n")) {
        const enum operator_t op_type = to_operator(token);
        if (op_type == op_invalid) {
            *stack++ = atof(token);
        } else {
            const double n2 = *--stack;
            const double n1 = *--stack;
            switch(op_type) {
                case op_add: *stack++ = n1 + n2; break;
                case op_sub: *stack++ = n1 - n2; break;
                case op_mul: *stack++ = n1 * n2; break;
                case op_div: *stack++ = n1 / n2; break;
                default: assert(0);
            }
        }
    }

    const double retval = stack_mem[0];
    free(str_copy);
    free(stack_mem);

    return retval;
}


void rpn_calc_test() {
    assert(rpn_calc("1 1 +") == 2);
    assert(rpn_calc("1 +1 -1 - +") == 3); // handle unary operators
    assert(rpn_calc("1 1 1 1 1 1 1 1 + + + + + + +") == 8);
    assert(rpn_calc("15 7 1 1 + - / 3 * 2 1 1 + + -") == 5);
    assert(fabs(rpn_calc("19 2.14 + 4.5 2 4.3 / - *") - 85.2974) < 1e-4);
}
