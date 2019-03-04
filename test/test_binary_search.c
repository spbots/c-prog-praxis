#include "../lib/binary_search.h"
#include <assert.h>

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
