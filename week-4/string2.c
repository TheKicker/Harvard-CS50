#include <stdio.h>

int main(void)
{
    char *s = "Hi!";
    
    printf("%p\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);
}

// output is
//
//  0x1234004
//  0x1234004
//  0x1234005
//  0x1234006
//  0x1234007