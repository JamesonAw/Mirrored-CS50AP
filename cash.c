// concern floating point value, track the amount of coins available
#include <stdio.h>
#include <math.h>
#include <cs50.h>
// to include the mathematical formulae to compute the various tabluations

int main()
{
    int cents_owed;
// the tabulation of the cents owed from the calculations
    do
    {
        float dollars_owed = get_float("Change owed: ");
        cents_owed = round(dollars_owed * 100);
    }
    while (cents_owed <= 0);
// intialize the count of cents owed to the nearest possible number in terms of numerical count
    int quarters = cents_owed / 25;
    int dimes = (cents_owed % 25) / 10;
    int nickels = ((cents_owed % 25) % 10) / 5;
    int pennies = ((cents_owed % 25) % 10) % 5;

    printf("%d\n", quarters + dimes + nickels + pennies);
}
