/*
** Exercise1.05.c
** Ad
** Init: 191003
*/

#include <stdio.h>

/* Print Fahrenheit-Celsius table for fahr = 300, 280, ..., 0. */
main()
{
    int fahr;

    for (fahr = 300; fahr >= 0; fahr = fahr - 20)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
}
