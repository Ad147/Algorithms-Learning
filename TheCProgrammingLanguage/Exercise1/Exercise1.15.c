// Exercise1-15.c
// Ad
// Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.

#include <stdio.h>

void printTemperature(int lower, int upper, int step);
float conversion(float fahr);

int main()
{
    int lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;

    printTemperature(lower, upper, step);

    return 0;
}

void printTemperature(int lower, int upper, int step)
{
    while (lower <= upper)
    {
        printf("%3.0f %6.1f\n", lower, conversion(lower));
        lower += step;
    }
}

float conversion(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}
