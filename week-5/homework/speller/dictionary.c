// Implements a dictionary's functionality
// https://manual.cs50.io/
#include <cs50.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // I really have to import one more library for compare strings?


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 65536;
unsigned int hash_value;
unsigned int word_count;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the word and get its value
    // access our list
    // go through the list and see if its in there
    // move to the next word
    hash_value = hash(word);
    node *current = table[hash_value];
    while (current != NULL)
    {
        if (strcasecmp(word, current->word) == 0)
        {
            return true;
        }
        current = current->next; // thanks tabnine for saving me time
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';

    // take in inputs which are alphabetical characters, regardless of case and possibly punctuation
    // return the hash of the word to check if it's value is correct

    // just have to create my own hash
    unsigned long hash = 5381;

    int c = *word;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open the dictionary
    // if the file is empty or crashes, return false
    // create space for the word
    // scan the entire dictionary ending at the EOF (end of file)
    // allocate the memory
    // again check for false or crash
    // initialize a pointer for the next node and the word itself
    // hash our word
    // set a new pointer
    // move the head to the new locartion
    // incrememnt our word count
    // always close our file
    // if the dictionary is loaded, return true, otherwise we return false
    // couldnt shake a memory segmentation error.
    // srushtikanade's code works though here
    FILE *file = fopen(dictionary, "r"); // open dict and read it, pointer to it is file
    if (file == NULL) // if the pointer points to null return
    {
        return false;
    }
    {
        // assign a buffer of size 1 for NTC
        char buffer[LENGTH + 1];
        while (fscanf(file, "%s", buffer) != EOF) // until eof
        {

            node *n = malloc(sizeof(node)); // allot memory for n
            if (n == NULL) // check if memory is alloted
            {
                fclose(file);
                return false;
            }
            else // if yes
            {
                strcpy(n->word, buffer); // copy word from buffer to word field of node n
                n->next = NULL; // at first the n node points to null
                unsigned int index = hash(buffer); // hash the word in buffer to get index of array
                // our current node points to what array is pointing at and then the array points to our node
                // even if our array points to null then this node points to null, it is better than initializing the array to null and then taking if/else
                n->next = table[index]; // this is done to avoid orphaning rest of the ll
                table[index] = n; // it gets inserted in beginning of ll
                word_count++; // increment the word count until eof
            }
        }
        fclose(file);
        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // check if there are any words in the dict
    // else return 0
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
    // that has to be it... rigth?
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // go through each bucket
    // set the curser to each bucket's head
    // if the cursor is not NULL, free it
    // if the cursor is null, return true
    for (int i = 0; i < N; i++)
    {
        node *current = table[i];
        while (current)
        {
            node *temp = current;
            current = current->next;
            free(temp);
        }
        if (i == N - 1 && current == NULL)
        {
            return true;
        }
    }
    return false;
}
