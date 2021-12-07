#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("What is your name?\n");
    //This string is getting your name.
    printf("Hello, %s\n", answer);
}