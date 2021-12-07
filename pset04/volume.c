// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t SAMPLE_AUDIO;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    BYTE header[HEADER_SIZE];
    // Copying header from input file to output file
    fread(header, sizeof(BYTE), HEADER_SIZE, input);
    fwrite(header, sizeof(BYTE), HEADER_SIZE, output);


    SAMPLE_AUDIO song;
    // Reading samples from input file and write updated data to output file
    while (fread(&song, sizeof(SAMPLE_AUDIO), 1, input) == 1)
    {
        song = song * factor;
        fwrite(&song, sizeof(SAMPLE_AUDIO), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
