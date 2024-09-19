#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long int fib_i_core[1000000];
unsigned long long int fib_r(unsigned long long int n)
{
    if (n == 0 || n == 1) {return 0;}
    if (n == 2) {return 1;}
    if (fib_i_core[n] != 0) {return fib_i_core[n];}
    else
    {
        fib_i_core[n] = fib_r(n - 1) + fib_r(n - 2);
        return fib_i_core[n];
    }
}

unsigned long long int fib_i(unsigned long long int n)
{
    unsigned long long int first = 0, second = 1;
    if (n == 0) {return 0;}
    if (n == 1 || n == 2) {return 1;}
    if (fib_i_core[n] != 0) {return fib_i_core[n];}
    else
    {
    	for (int i = 2; i < n; ++i)
    	{
    		fib_i_core[n] = first + second;
    		first = second;
    		second = fib_i_core[n];
    	}
    }
    return fib_i_core[n];
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
