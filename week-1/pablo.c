#include <stdio.h>

// first void is what the function is returning, in this case nothing it just prints
// meow is the name of our custom function
// meow takes in one parameter of int type that we call n
void meow(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("meow \n");
    }
}

int main(void)
{
    meow(5);
}