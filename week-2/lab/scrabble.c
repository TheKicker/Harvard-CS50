#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner (self explanatory)
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    // i will allow us to step through the word to length
    for (int i = 0; i < strlen(word); i++)
    {
        // if the letter is upper, subtract the value of A to give us a 1-26 range
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 65];
        }
        // if the letter is upper, subtract the value of a to give us a 1-26 range
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 97];
        }
    }
    return score;
}
