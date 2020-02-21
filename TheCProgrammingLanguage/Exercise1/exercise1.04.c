/*
** Exercise1.04.c
** Ad
** Init: 191002
*/

#include <stdio.h>

/* Print Celsius-Fahrenheit table for celsius = 0...100. */
main()
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 100;
    step = 10;

    celsius = lower;
    while (celsius <= upper)
    {
        fahr = celsius * (9.0 / 5.0) + 32.0;
        printf("%3.0f %6.0f\n", celsius, fahr);
        celsius += step;
    }
}
