// Exercise1-4.c
// Ad
// Write a program to print the corresponding Celsius to Fahrenheit table.

#include <stdio.h>

// print Celsius-Fahrenheit table for celsius = 0...100
int main()
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 100;
    step = 10;

    printf("Temperature Conversions\n");
    printf("Celsius Fahrenheit\n");

    celsius = lower;
    while (celsius <= upper)
    {
        fahr = celsius * (9.0 / 5.0) + 32.0;
        printf("%7.1f %10.1f\n", celsius, fahr);
        celsius += step;
    }
}
