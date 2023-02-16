// Modifies the volume of an audio file
#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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

    // TODO: Copy header from input file to output file
    // three glass problem from lecture
    // use the uint8_t and uint16_t from lab instructions
    // I keep wanting to write unit8_t
    uint8_t header[HEADER_SIZE];

    // https://manual.cs50.io/
    fread(&header, sizeof(header), 1, input);
    fwrite(&header, sizeof(header), 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // read and write an exact clone
    int16_t buffer;
    // for loop didn't work.  Created an output file but totally silent.
    //
    // for (int i = 0; i < HEADER_SIZE; i++)
    // {
    //     fread(&buffer, sizeof(uint8_t), 1, input);
    //     fwrite(&buffer, sizeof(uint8_t), 1, output);
    // }
    //
    // going to try a while loop instead
    //
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // why addition, shouldn't we be multiplying the factor?
        // so 5 * 0.5 would be half as loud
        //      5 + 0.5 would be slightly louder
        // I'm confused.
        // Now it works when I use the right sizeof(value).  I'm dumb.
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
