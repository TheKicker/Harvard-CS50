#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Create a variable called height
    int height;
    // Do this as long as height is less than 8 and greater than 1
    do{
        // Prompt the user
        height = get_int("Height of pyramid: ");
    }
    while(height < 1 || height > 8); // Make sure its in range

    // For rows
    for (int row = 0; row < height; row++)
    {
        // For columns
        for (int space = height - row - 1; space > 0; space--)
        {
            printf(" "); // print a space
        }
        // to print a step
        for (int step = 0; step < row + 1; step++)
        {
            printf("#"); // print a block
        }
        // go to next line
        printf("\n");
    }
}