#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Word: ");

    int i = 0;
    while (name[i] != '\0');
    {
        i++;
    }
    printf("%i\n", i);
    // hi! prints 3
    // bye! prints 4
    // kicker prints 6
}