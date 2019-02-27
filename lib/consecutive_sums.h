#ifndef consecutive_sums_h
#define consecutive_sums_h

/*
https://programmingpraxis.com/2019/02/12/consecutive-sums/
Consecutive Sums
February 12, 2019

Given the positive integer 15, there are three ways to take consecutive
positive integers that sum to 15: 1+2+3+4+5, 4+5+6 and 7+8.

Your task is to write a program that, given a positive integer, finds
all the ways that consecutive positive integers can sum to the target
integer.

---

the implementation of the function seems straightforward to me:
consecutive_sums(n)
    for k in 2..(n/2)
        if k is even && n % k == (k/2)
            ... e.g. n == 18, k == 4 (3+4+5+6)
        if k is odd && n % k == 0
            ... e.g. n == 18, k == 3 (5+6+7)

but i have no idea what a good function signature for this looks
like in c! in c++ i would probably return a vector<vector<int>>,
with each inner vector containing the numbers to be summed (e.g.
c_s(18) -> [[3,4,5,6],[5,6,7]]) but i don't know if that is a
responsible decision in c.

another alternative return type, although it still requires
allocating an array, could be a collection of pairs of (start
number, size), such that c_s(15) -> [(1,5), (4,3), (7,2)].

some concrete questions:
- is this return type correct?
- is it okay to push mem mgmt to client?
- is it preferable for the client to pass in a pointer instead?
- if i do need to allocate and return memory, it it "good form"
    to realloc the returned memory to the minimum size?
*/

/*
A collapsed representation of a consecutive sum.

e.g sum_start: 3, consecutive_numbers: 4 means that
this represents a sum of 3+4+5+6
*/
struct sum_numbers {
    int sum_start;
    int consecutive_numbers;
};
typedef struct sum_numbers SumNumbers;

struct sum_numbers_array {
    SumNumbers* a;
    int size;
};
typedef struct sum_numbers_array SumNumbersArray;

SumNumbersArray consecutive_sums(const int n);
void consecutive_sums_test();

#endif
