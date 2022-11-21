#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// bool only_digits(string s);

int main(int argc, string argv[])
{
    // Collect input from the user on the key
    // Argc is the count of arguments given, so in this case filename and shift
    // Argv is the actual array of elements
    if (argc == 2 && isdigit(*argv[1]))
    {
        // Get the key value
        int key = atoi(argv[1]);

        // Get the plain text input
        string plain = get_string("plaintext: ");
        int length = strlen(plain);
        // printf("%s\n",plain);
        printf("ciphertext: ");

        // Output cypher text shifted by number
        for (int i = 0; i < length; i++)
        {
            // Preserve case
            // printf("%c\n", plain[i]); // debugging purposes
            if (plain[i] >= 'a' && plain[i] <= 'z')
            {
                // if the letter is within a-z
                // take the current letter subtract 97, add our key, take the modulus 26, add 97 again
                printf("%c", (((plain[i] - 'a') + key) % 26) + 'a');
            }
            else if (plain[i] >= 'A' && plain[i] <= 'Z')
            {
                // if the letter is within A-Z
                // take the current letter subtract 65, add our key, take the modulus 26, add 65 again
                printf("%c", (((plain[i] - 'A') + key) % 26) + 'A');
            }
            else
            {
                // Anything else, 0-9 or punctuation, ignore and pass the char right back
                printf("%c", plain[i]);
            }
        }
        // For prettier formatting
        printf("\n");
        // Exit by returning 0 from main
        return 0;
    }
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}

// bool only_digits(char s)
// {
//     // From https://stackoverflow.com/questions/14422775/how-to-check-a-given-string-contains-only-number-or-not-in-c
//     while (*s)
//     {
//         if (isdigit(*s++) == 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }