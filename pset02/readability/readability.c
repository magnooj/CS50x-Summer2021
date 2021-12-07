#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// I got the main idea of this solution from this youtube video: https://www.youtube.com/watch?v=BuD1biyAKnM
int main(void)
{
    string input = get_string("Text: ");
    //Defining the Arguments.
    int word = 1;
    int sent = 0;
    int letter = 0;

    //Checking and calculating arguments.
    for (int i = 0; i < strlen(input); i++)
    {
        if (isalpha(input[i]))
        {
            letter++;
        }
        else if ((i == 0 && input[i] != ' ') || (i != (strlen(input) - 1) && input[i] == ' ' && input[i + 1] != ' '))
        {
            word++;
        }
        else if ((input[i] == '.') || (input[i] == '?') || (input[i] == '!'))
        {
            sent++;
        }
    }

    //Calculating coleman index.
    float L = (letter / (float) word) * 100;
    float S = (sent / (float) word) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    //Printing result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}