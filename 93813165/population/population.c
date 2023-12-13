#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n;
    do
    {
        n = get_int("start size: ");
    }
    while (n < 9);

    // TODO: Prompt for end size
    int i;
    do
    {
        i = get_int("End size: ");
    }
    while (i < n);

    // TODO: Calculate number of years until we reach threshold
    int y = 0;
    for (int p = n; p < i; y++)
    {
        p = p + (p / 3) - (p / 4);
    }
    // TODO: Print number of years
    printf("Years: %i\n", y);
}
