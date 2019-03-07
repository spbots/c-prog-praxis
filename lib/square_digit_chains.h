#ifndef square_digit_chains_h
#define square_digit_chains_h

/*
https://programmingpraxis.com/2018/10/19/square-digit-chains/
Square Digit Chains
October 19, 2018

Today’s task appears on Project Euler, Rosetta Code, and Sloane’s,
so it is well worth a look; we even did a version of this task in
a previous exercise. Here is the Project Euler version of the problem:

A number chain is created by continuously added the square of the digits
of a number to form a new number until it has been seen before. For example:

    44 → 32 → 13 → 10 → 1 → 1
    85 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58 → 89

Therefore any chain that arrives at 1 or 89 will become stuck in an
endless loop. What is most amazing is that EVERY starting number
will eventually arrive at 1 or 89.

How many starting numbers below ten million will arrive at 89?
*/
void square_digit_chains_test();

#endif // square_digit_chains_h
