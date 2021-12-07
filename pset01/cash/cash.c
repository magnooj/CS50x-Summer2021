#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        // getting change owed
        change = get_float("How much is the change owed in dollars? ");
    }
    while (change < 0);

    // changing dollar to cent
    int cents = round(change * 100);

    // defining variables
    // qu = quarter, di = dime, te = ten
    // r = ramaining change
    int qu = cents / 25;
    int rqu = cents % 25;
    int di = rqu / 10;
    int rdi = rqu % 10;
    int te = rdi / 5;
    int rte = rdi % 5;

    // coins
    int coins = qu + di + te + rte;

    // printing number of coins
    printf("%i\n", coins);

}