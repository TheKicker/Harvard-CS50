#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // Lets loop through the candiddates counts
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is what the user voted
        // use strcmp from lecture
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If it is, add to the vote count
            candidates[i].votes++;
            return true;
        }
    }
    // If it is not, print invalid and continue
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // set a variable for the maximum votes allowed
    int max_vote = 0;
    // go through the list of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // check for candidates whose votes exceed the maximum, and set them as max
        if (candidates[i].votes > max_vote)
        {
            max_vote = candidates[i].votes;
        }
    }

    // iterate again
    for (int x = 0; x < candidate_count; x++)
    {
        // check for candidates whose votes exceed the maximum, and set them as max
        if (candidates[x].votes == max_vote)
        {
            // please work
            printf("%s\n", candidates[x].name);
        }
    }
    // if the candidate is the maximum, print his/her name as winner winner chicken dinner

    return;
}