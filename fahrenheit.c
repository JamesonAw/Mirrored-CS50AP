#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // Asking user for temperature in Celsius(°C)

    printf("Temperature in C: ");

    float C = GetFloat();

    // Converts C to F

    float F = ((C * 9) / 5) + 32;


    // Displays result


    printf("The temperature in Fahrenheit is %.1f\n", F);

}