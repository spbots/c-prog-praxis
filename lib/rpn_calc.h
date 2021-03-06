#ifndef rpn_calc_h
#define rpn_calc_h

/*
https://programmingpraxis.com/2009/02/19/rpn-calculator/
RPN Calculator
February 19, 2009

Implement an RPN calculator that takes an expression like
19 2.14 + 4.5 2 4.3 / - * which is usually expressed as
(19 + 2.14) * (4.5 - 2 / 4.3) and responds with 85.2974.

The program should read expressions from standard input and
print the top of the stack to standard output when a newline
is encountered. The program should retain the state of the
operand stack between expressions.
*/
double rpn_calc(const char* str);
void rpn_calc_test();

#endif
