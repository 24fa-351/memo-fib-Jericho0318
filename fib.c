#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

uint64_t fib_r_core(int fibIndex)
{
    if (fibIndex == 0 || fibIndex == 1) {return 0;}
    if (fibIndex == 2) {return 1;}
    else {
        if (fib_r_core(fibIndex - 1) > ULLONG_MAX - fib_r_core(fibIndex - 2))
        {
            printf("Error: overflow\nMax value: %lu\n", fib_r_core(fibIndex - 1));
            exit(1);
        }
    }
    return fib_r_core(fibIndex - 1) + fib_r_core(fibIndex - 2);
}

uint64_t fib_i_core(int fibIndex)
{
    uint64_t first = 0, second = 1, sum = 0;
    if (fibIndex == 0) {return 0;}
    if (fibIndex == 1 || fibIndex == 2) {return 0;}
    else
    {
        for (int i = 2; i < fibIndex; ++i)
        {
            if (second > ULLONG_MAX - first)
            {
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

uint64_t memoize(fib_func func, uint64_t fibIndex) {
    if (memcache == NULL) {
        memcache = (uint64_t*)malloc((fibIndex + 1) * sizeof(uint64_t));
        for (int i = 0; i <= fibIndex; i++) {
            memcache[i] = -1;
        }
    }

    if (memcache[fibIndex] == -1) {
        memcache[fibIndex] = func(fibIndex);
    }

    return memcache[fibIndex];
}

uint64_t fib_r(int fibIndex) {
    if (fibIndex == 0 || fibIndex == 1) {return 0;}
    if (fibIndex == 2) {return 1;}
    else 
    {
        if (memoize(fib_r, fibIndex - 1) > ULLONG_MAX - memoize(fib_r, fibIndex - 2))
        {
            printf("Error: overflow\nMax value: %lu\n", fib_r(fibIndex - 1));
            exit(1);
        }
        return memoize(fib_r, fibIndex - 1) + memoize(fib_r, fibIndex - 2);
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
