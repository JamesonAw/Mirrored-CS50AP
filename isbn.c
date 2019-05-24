#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Declaring Variables
    int ithDigit;
    int sum = 0;

    // Retrieve ISBN
    printf("ISBN: ");
    long long isbn = GetLongLong();


    //Find the sum of digits with multiple factorisations
    for (int i = 10 ; i >= 0; i--)

    {
        ithDigit = isbn % 10;
        sum += (ithDigit * i);
        isbn = isbn / 10;
    }

       if (sum % 11 == 0)

    {
        printf("YES\n");
    }
       else
    {
        printf("NO\n");
    }
}

//end of code execution
