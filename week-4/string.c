#include <cs50.h>
#include <stdio.h>

//
//  Remember that C adds our null or escape value automatically
//  So a string of "Hi!" is actually represented as
//  H i ! \0 
//  in the computers memory.  
//
//  And since strings dont actually exist in C, we've been using a library
//  which marks the first character in a string, and the computer goes
//  automatically until it hits the escape operator to return our string
//
//  So strings are basically an alias for *c or the pointer for the first char
//

int main(void)
{
    string s = "Hi!";
    char *p = &s[0];
    
    printf("%p\n", p);
    printf("%p\n", s);
}