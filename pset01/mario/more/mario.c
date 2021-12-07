#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int hash;
    do
    {
        // take height of jump
        hash = get_int("What height you want to mario jump? (It should be between 1 to 8)\nHeight: ");
    }
    while (hash > 8 || hash < 1);

    for (int i = 0; i < hash ; i++)
    {
        // counting and printing spaces
        for (int k = hash - 1; k > i; k--)
        {
            printf(" ");
        }

        // counting and printing hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // printing valley
        printf("  ");

        // printing other hashes
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}