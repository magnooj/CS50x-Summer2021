#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long x = get_long("x: ");
    int y = get_int("y: ");

    printf("sum is %ld\n", x + y);
}