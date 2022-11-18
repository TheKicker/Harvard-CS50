#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = get_int("How many test scores do you have? ");
    int scores[n];

    for (int i=0; i<n; i++)
    {
        scores[i] = get_int("Enter score: ");
    }

    int avg = ((scores[0] + scores[1] + scores[2])/ n);
    printf("Average: %f\n", avg);
}

printf("Null is the hero: \0");