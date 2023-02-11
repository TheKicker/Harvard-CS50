#include <stdio.h>

int main(void)
{
    // ints take up 4 bytes or 32 bits of memory
    int n = 50;
    // single ampersand is the "address of operator"
    // letting us literally in our code find the address of that in the computer memory
    // here we will store it in a variable via an asterisk operator before the name of the variable
    int *p = &n;
    // prints our int
    printf("%i\n", n);
    // prints the location of that int
    printf("%p\n", p);
}