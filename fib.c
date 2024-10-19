#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100


unsigned long long int memo[MAX];
unsigned long long int fib_r_core(unsigned long long int n)
{
    if (n == 0 || n == 1) {return 0;}
    if (n == 2) {return 1;}
    if (fib_r_core(n - 1) > ULLONG_MAX - fib_r_core(n - 2))
        {
            printf("Error: overflow\nMax value: %llu\n", fib_r_core(n - 1));
            exit(EXIT_FAILURE);
        }
    return fib_r_core(n - 1) + fib_r_core(n - 2);
}

unsigned long long int fib_i_core(unsigned long long int n)
{
    unsigned long long int first = 0, second = 1, sum = 0;
    if (n == 0) {return 0;}
    if (n == 1 || n == 2) {return 1;}
    else
    {
        for (int i = 2; i < n; ++i)
        {
            if (second > ULLONG_MAX - first)
            {
                printf("Error: overflow\nMax value: %llu\n", second);
                exit(EXIT_FAILURE);
            }
            sum = first + second;
            first = second;
            second = sum;
        }
    }
    return sum;
}

unsigned long long int fib_r(unsigned long long int n)
{
    if (n == 0 || n == 1) {return 0;}
    if (n == 2) {return 1;}
    if (memo[n] != 0) {return memo[n];}
    else
    {
        if (fib_r(n - 1) > ULLONG_MAX - fib_r(n - 2))
        {
            printf("Error: overflow\nMax value: %llu\n", fib_r(n - 1));
            exit(EXIT_FAILURE);
        }
        memo[n] = fib_r(n - 1) + fib_r(n - 2);
        return memo[n];
    }
}

unsigned long long int fib_i(unsigned long long int n)
{
    unsigned long long int first = 0, second = 1;
    if (n == 0) {return 0;}
    if (n == 1 || n == 2) {return 1;}
    if (memo[n] != 0) {return memo[n];}
    else
    {
    	for (int i = 2; i < n; ++i)
    	{
            if (second > ULLONG_MAX - first)
            {
                printf("Error: overflow\nMax value: %llu\n", second);
                exit(EXIT_FAILURE);
            }
    		memo[n] = first + second;
    		first = second;
    		second = memo[n];
    	}
    }
    return memo[n];
}

int main(int argc, char *argv[])
{
    unsigned long long int num = atoi(argv[1]);
    if (!strcmp(argv[2], "i"))
    {
        printf("%llu\n", fib_i(num));
    } else if (!strcmp(argv[2], "r")) {
        printf("%llu\n", fib_r(num));
    }
    return 0;
}
