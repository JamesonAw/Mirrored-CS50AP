#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
int main(int argc, string argv[])
{
    int j;
    int k;
    int l = 0;
    //Make sure there is only one command line argument
    if (argc != 2)
    {
        printf("Try Again\n");
        return 1;
    }
    string s = (argv[1]);
    //Make sure command line argument is alpha
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]) == false)
        {
            printf("Try Again\n");
            return 1;
        }
    }
    //Get user input string
    string plainText = get_string("plaintext: ");
    //Place to print cipher text
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plainText); i++)
    {
        //Encrypt lower case
        if islower(plainText[i])
        {
            j = (l % strlen(s));
            k = (tolower(s[j]) - 97);
            printf("%c", (((plainText[i] + k) - 97) % 26) + 97);
            l += 1;
        }
        //encrypt upper case
        else if isupper(plainText[i])
        {
            j = (l % strlen(s));
            k = (tolower(s[j]) - 97);
            printf("%c", (((plainText[i] + k) - 65) % 26) + 65);
            l += 1;
        }
        //print anything else
        else
        {
            printf("%c", plainText[i]);
        }
    }
    printf("\n");
    return 0;
}