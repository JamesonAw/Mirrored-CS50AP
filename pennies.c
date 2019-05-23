// CS50/Pset1/Pennies.c Directory

//Ask for the amt of days within a month, check for valid days, and subsequently snowball the compounded pennies accordingly.

// Jameson

#include <cs50.h>
#include <stdio.h>
#include <math.h>


int
main(void)

{
    //Variable
    int days = 0 ;
int pennies = 0 ;
// ask for how many days <n>, within the month
//  check for valid days after defining the various variables
    do
    {
    printf("Days in Month: ");
    days = get_float();
    }
    while (days < 28 || days > 31);
// checks to make sure that value is 28,29,30,31

// ask how many pennies present within the first day, establishing positive values

    do
    {
    printf("Pennies on First Day: ");
    pennies = get_float();
    }
    while (pennies <= 0);


// total sum of pennies
long long total = 0;
for (int i = 0; i < days; i++)
{
    total += pennies;
pennies *= 2;
}
double dollar = ((double) total / 100);
    printf("$%.2f\n", dollar);

    exit(0);
}

