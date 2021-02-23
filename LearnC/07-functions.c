#include <stdio.h>

int main()
{
    printf("%d\n", recursivePower(5, 3));
    return 0;
}

int power(int input, int exponent)
{      
    int total = 1;
    for (int i = 0; i < exponent ; i++) 
    {
        total *= input;
    }
    return total;
}

int recursivePower(int input, int exponent)
{
    if (exponent < 1) //base case
    { 
        return 1;
    }
    return input * recursivePower(input, exponent-1);
}

// in order to change a value in the whole function we need pointers. check out 08-pointers.
// to learn how to make a library out of your functions check the below link at 02:08':00".
// link to resource: https://www.youtube.com/watch?v=1uR4tL-OSNI