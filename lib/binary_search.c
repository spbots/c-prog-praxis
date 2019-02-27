#include "binary_search.h"

#include <assert.h>

int binary_search(const int x, const int* arr, const int size) {
    if (!arr || !size || x < arr[0] || x > arr[size-1]) return -1;

    const int chop = size/2;
    const int odd_size = !(size%2);
    if (arr[chop] == x) {
        return chop;
    } else if (x < arr[chop]) {
        return binary_search(x, arr, chop);
    } else {
        const int result =
            binary_search(x, arr + chop + 1, chop - odd_size);
        return result != -1 ? (chop + 1 + result) : -1;
    }
}

void binary_search_test() {
    static const int sz = 1000;
    int arr[sz];

    for (int i = 0; i < sz; ++i) {
        arr[i] = i * 2;
    }

    for (int i = 0; i < sz; ++i) {
        assert(binary_search(i * 2, arr, sz) == i);
        assert(binary_search(i * 2 - 1, arr, sz) == -1);
    }
}
