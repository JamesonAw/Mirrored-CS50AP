// Greets a user by their name

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    //check correct argc
    if (argc != 2)
    {
        printf("Usage: ./hello <name>\n");
        return 1;

    }
    // collects a string from the user, then prints their corresponding name
    printf("Hello, %s!\n", argv[1]);
}
