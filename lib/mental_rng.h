#ifndef mental_rng_h
#define mental_rng_h

/*
https://programmingpraxis.com/2019/01/29/marsaglias-mental-rng/
Marsaglia’s Mental RNG
January 29, 2019

We saw an “in-your-head” random number generator in a previous exercise,
but I found it hard to operate. Today’s exercise, due to George Marsaglia
is a random number generator that even a dummy like me can work in his head:

Choose a two-digit number as a seed. Then form a new two-digit number by
adding the ten’s digit and six times the unit digit. For instance, if you
start from 23, the sequence is 23 → 20 → 02 → 12 → 13 → 19 → 55 → 35 ….
Then the sequence of random digits is the unit digit of each two-digit
number. This operation produces the numbers 1 through 58 as seeds; the
ten digits each occur six times, except that nine and zero occur five
times (because 59 and 60 are not part of the sequence).
*/
struct mental_rng;

struct mental_rng* create_mental_rng(const int seed);
void destroy_mental_rng(struct mental_rng* rng);
int get_rand(struct mental_rng* rng);

void mental_rng_test();

#endif // mental_rng_h
