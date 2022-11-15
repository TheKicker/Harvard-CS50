#include <stdio.h>
#include <cs50.h>

float discount(float r, int p)
{
    return r * (100 - p) / 100;
}

int main(void)
{
    float regular = get_float("Regular price: ");
    int percent = get_int("Percent off: ");
    float sale = discount(regular, percent);
    printf("Sale price: %.2f\n", sale)
}