#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

unsigned long long int fib_r_core(int fibIndex)
{
    if (fibIndex == 0 || fibIndex == 1) {return 0;}
    if (fibIndex == 2) {return 1;}
    if (fib_r_core(fibIndex - 1) > ULLONG_MAX - fib_r_core(fibIndex - 2))
        {
            printf("Error: overflow\nMax value: %llu\n", fib_r_core(fibIndex - 1));
            return 1;
        }
    return fib_r_core(fibIndex - 1) + fib_r_core(fibIndex - 2);
}

unsigned long long int fib_i_core(int fibIndex)
{
    unsigned long long int first = 0, second = 1, sum = 0;
    if (fibIndex == 0) {return 0;}
    if (fibIndex == 1 || fibIndex == 2) {return 0;}
    else
    {
        for (int i = 2; i < fibIndex; ++i)
        {
            if (second > ULLONG_MAX - first)
            {
                printf("Error: overflow\nMax value: %llu\n", second);
                return 1;
            }
            sum = first + second;
            first = second;
            second = sum;
        }
    }
    return sum;
}

typedef unsigned long long int (*fib_func)(int);

unsigned long long int *memcache = NULL;

unsigned long long int memoize(fib_func func, unsigned long long int fibIndex) {
    if (memcache == NULL) {
        memcache = (unsigned long long int*)malloc((fibIndex + 1) * sizeof(unsigned long long int));
        for (int i = 0; i <= fibIndex; i++) {
            memcache[i] = -1;
        }
    }

    if (memcache[fibIndex] == -1) {
        memcache[fibIndex] = func(fibIndex);
    }

    return memcache[fibIndex];
}

unsigned long long int fib_r(int fibIndex) {
    if (fibIndex == 0 || fibIndex == 1) {return 0;}
    if (fibIndex == 2) {return 1;}
    else 
    {
        if (memoize(fib_r, fibIndex - 1) > ULLONG_MAX - memoize(fib_r, fibIndex - 2))
        {
            printf("Error: overflow\nMax value: %llu\n", fib_r(fibIndex - 1));
            return 1;
        }
        return memoize(fib_r, fibIndex - 1) + memoize(fib_r, fibIndex - 2);
    }
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("./fib <number> <r or i>\n");
        return 1;
    }

    unsigned long long int number_to_fib = atoi(argv[1]);

    if (!strcmp(argv[2], "i")) {
        printf("%llu\n", memoize(fib_i_core, number_to_fib));
    } else if (!strcmp(argv[2], "r")) {
        printf("%llu\n", memoize(fib_r, number_to_fib));
    }

    free(memcache);

    return 0;
}
