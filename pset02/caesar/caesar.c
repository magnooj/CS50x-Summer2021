#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//I got the idea of solving this pset from this video: https://www.youtube.com/watch?v=c_sQKoAhvf8
int main(int argc, string argv[])
{
    //checking number and type of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]) % 26; //turning k to a smaller remainer

    //getting plaintext
    string plaintext = get_string("plaintext: ");

    //ciphering
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
            continue;
        }
        //setting characters to a list that started from zero
        int ascii = isupper(plaintext[i]) ? 65 : 97;

        int pi = plaintext[i] - ascii;
        int ci = ((pi + k) % 26) + ascii;

        printf("%c", ci);
    }
    printf("\n");
}