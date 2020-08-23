#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int quarter = 25, dime = 10, nickel = 5, penny = 1, count = 0;
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    int cents = round(dollars * 100);

    while (cents > 0)
    {
        if ((cents - quarter) >= 0)
        {
            cents -= quarter;
            count++;
            continue;
        }
        else if ((cents - dime) >= 0)
        {
            cents -= dime;
            count++;
            continue;
        }
        if ((cents - nickel) >= 0)
        {
            cents -= nickel;
            count++;
            continue;
        }
        else
        {
            cents -= penny;
            count++;
        }
    }

    printf("%i\n", count);
}