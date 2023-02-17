#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover <filename>\n"); // Thanks tabnine
        return 1;
    }

    // open the input file
    FILE *file_pointer = fopen(argv[1], "r");
    if (!file_pointer)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    // set output file pointer to null
    FILE *output_file_pointer = NULL;

    // create a byte array to hold the file data
    BYTE buffer[512];

    // init a count of the total number of images found
    int total_images = 0;

    // init a string to hold the file name
    char file_name[30];

    // read the memory card until the end
    while (fread(buffer, sizeof(BYTE) * 512, 1, file_pointer) == 1) // thanks tabnine
    {
        printf("Start yerrrrrr engines");
        // check if a JPEG has been found
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // close output file pointer if jpeg was already found
            if (output_file_pointer != NULL)
            {
                fclose(output_file_pointer);
            }

            // sprintf stands for string print
            // sprintf (char *str, const char *format, ...)
            sprintf(file_name, "card-%03d.jpg", total_images++); // i trusted you tabnine
            // write the file
            output_file_pointer = fopen(file_name, "w"); // thanks tabnine
        }
        if (output_file_pointer != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, output_file_pointer);
        }
    }

    if (output_file_pointer != NULL)
    {
        fclose(output_file_pointer);
    }

    fclose(file_pointer);

    return 0;
}