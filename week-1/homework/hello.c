#include <stdio.h>
#include <cs50.h> // for get_string function

int main(void)
{
    // Get the input from the user
    string name = get_string("What's your name? ");
    // Insert their response into hello, _____
    printf("hello, %s\n", name);
}