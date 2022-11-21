#include <cs50.h>
#include <stdio.h>
// In order to use StrLen()
#include <string.h>
// Library from: https://stackoverflow.com/questions/8611815/determine-if-char-is-a-num-or-letter
#include <ctype.h>
// Library from: https://iq.opengenus.org/rounding-and-truncating-numbers-in-c/#:~:text=round()
#include <math.h>

int main(void)
{
    int letters = 0;
    int words = 0;
    int sentences = 0;

    string input = get_string("Text: ");
    int length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        // Get the current character
        char c = input[i];
        // Check if alphabetical
        if (isalpha(c))
        {
            letters++;
        }
        // Check for spaces
        if (c == ' ')
        {
            words++;
        }
        // Check for punctuation
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }

    // Getting too high of a score because last word was being left off
    // this adds one to the final total to correct the formula below
    words = words + 1;

    // printf("%i - Letters \n %i - Words \n %i - Sentences \n", letters, words, sentences);

    // Coleman-Liau Index
    float L = ((float)letters / (float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int indexRounded = round(index);
    if (indexRounded > 16)
    {
        printf("Grade 16+\n");
    }
    else if (indexRounded < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", indexRounded);
    }
}