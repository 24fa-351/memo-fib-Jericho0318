#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t fib_r_core(int num_to_fib) {
    if (num_to_fib == 0 || num_to_fib == 1)
        return 0;
    if (num_to_fib == 2) {
        return 1;
    } else if (fib_r_core(num_to_fib - 1) >
               ULLONG_MAX - fib_r_core(num_to_fib - 2)) {
        printf("Error: overflow\nMax value: %lu\n", fib_r_core(num_to_fib - 1));
        exit(1);
    }
    return fib_r_core(num_to_fib - 1) + fib_r_core(num_to_fib - 2);
}

uint64_t fib_i_core(int num_to_fib) {
    uint64_t first = 0, second = 1, sum = 0;
    if (num_to_fib == 0)
        return 0;
    if (num_to_fib == 1 || num_to_fib == 2) {
        return 0;
    } else {
        for (int i = 2; i < num_to_fib; ++i) {
            if (second > ULLONG_MAX - first) {
                printf("Error: overflow\nMax value: %lu\n", second);
                exit(1);
            }
            sum = first + second;
            first = second;
            second = sum;
        }
    }
    return sum;
}

typedef uint64_t (*fib_func)(int);

uint64_t *memcache = NULL;

uint64_t memoize(fib_func func, uint64_t num_to_fib) {
    if (memcache == NULL) {
        memcache = (uint64_t *)malloc((num_to_fib + 1) * sizeof(uint64_t));
        for (int ix = 0; ix <= num_to_fib; ix++) memcache[ix] = -1;
    }

    if (memcache[num_to_fib] == -1)
        memcache[num_to_fib] = func(num_to_fib);

    return memcache[num_to_fib];
}

uint64_t fib_r(int num_to_fib) {
    if (num_to_fib == 0 || num_to_fib == 1)
        return 0;
    if (num_to_fib == 2) {
        return 1;
    } else {
        if (memoize(fib_r, num_to_fib - 1) >
            ULLONG_MAX - memoize(fib_r, num_to_fib - 2)) {
            printf("Error: overflow\nMax value: %lu\n", fib_r(num_to_fib - 1));
            exit(1);
        }
        return memoize(fib_r, num_to_fib - 1) + memoize(fib_r, num_to_fib - 2);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("./fib <number> <r or i>\n");
        exit(1);
    }

    uint64_t number_to_fib = atoi(argv[1]);

    if (!strcmp(argv[2], "i")) {
        printf("%lu\n", memoize(fib_i_core, number_to_fib));
    } else if (!strcmp(argv[2], "r")) {
        printf("%lu\n", fib_r(number_to_fib));
    } else {
        perror("Choose between i or r in argv[2]\n");
        exit(1);
    }

    free(memcache);

    return 0;
}
