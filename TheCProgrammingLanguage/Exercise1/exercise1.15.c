/*
** Exercise1-15.c
** Ad
** Init: 191006
*/

#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float celsius(float fahr);

/* print Fahrenheit-Celsius table */
main()
{
    float fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr += STEP)
        printf("%3.0f %6.1f\n", fahr, celsius(fahr));

    return 0;
}

/* convert Fahrenheit temperature to Celsius */
float celsius(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}
