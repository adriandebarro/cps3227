#include <stdio.h>
#include <stdlib.h>

/*
 * prototyping example
 */
int Addition(int a, int f);

/*
 * Subtraction function
 */
int Subtraction(int p_var1, int p_var2)
{
    return p_var1 - p_var2;
}

typedef void (*CallbackFunctionPrint)(int a);
typedef int (*CallbackFunctionOP)(int,int);

void Print(int p_x)
{
    printf("%d, \n", p_x);
}

void Calculate(CallbackFunctionOP ans,int p_x, int p_y, CallbackFunctionPrint p_callbackFunction )
{
    int result = ans(p_x,p_y);
    p_callbackFunction(result);
}

/*
 * Main method
 */
int main(void)
{
    int add = Addition(5, 5);
    int sub = Subtraction(5, 5);
    printf("The addition is equal %d \n", add);
    printf("The subtraction is equal to %d \n", sub);


    Calculate(Subtraction,10,5,Print);
    Calculate(Addition,10,25,Print);
    return 0;
}

/*
 * Addition function prototyped
 */
int Addition(int p_var1, int p_var2)
{
    return p_var1 + p_var2;
}