// Prints a 3-by-3 grid of bricks with nested loops
#include <stdio.h>

int main(void)
{
    // For row
    for (int i = 0; i < 3; i++)
    {
        // For column
        for (int j = 0; j < 3; j++)
        {
            // Print a brick
            printf("#");
        }
        printf("\n");
    }
}