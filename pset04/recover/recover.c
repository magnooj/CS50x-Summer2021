#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKSIZE 512
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // checking the file is readable
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    char *inputPtr = argv[1];
    if (inputPtr == NULL)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char filename[8]; // for "###.jpg'\0'" the buffer for file name
    FILE *output;
    BYTE buffer[BLOCKSIZE]; // allocating memory for recovery
    int counter = 0; // counting the number of image recovered

    while (fread(buffer, BLOCKSIZE, 1, inputFile) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (counter != 0)
            {
                fclose(output); //Close previous image
            }
            sprintf(filename, "%03i.jpg", counter);
            output = fopen(filename, "w");
            fwrite(buffer, BLOCKSIZE, 1, output);
            counter++;
        }
        else if (counter > 0)
        {
            fwrite(buffer, BLOCKSIZE, 1, output);
        }
    }

    return 0;
}