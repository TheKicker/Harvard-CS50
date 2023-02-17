#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// To prevent undeclared identifier for BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // printf("Your argc is: %i \n", argc);
    // take in and parse the command line args
    if (argc != 2)
    {
        // print all of the args (for debugging)
        // for (int i = 0; i < argc; i++)
        // {
        //     printf("%s ", argv[i]);
        // }
        // printf("\n");

        printf("Usage: ./ recover image\n");
        return 1;
    }
    else
    {
        // printf("Start yerr engines\n");
        // open the file
        char *input_file = argv[1];
        printf("Input file: %s\n", input_file);
        FILE *input_pointer = fopen(input_file, "r");
        // check if the input_pointer is valid
        if (input_pointer == NULL)
        {
            printf("Error opening file %s\n", input_file); // thanks Tabnine
            printf("Error opening file %p\n", input_pointer);
            return 2;
        }

        // init variables
        BYTE buffer[512];
        int i = 0;
        FILE *image_pointer = NULL;
        char filename[8];

        // do stuff (the whole card.raw file)
        // https://www.tutorialspoint.com/c_standard_library/c_function_fread.html
        // fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
        //      ptr − This is the pointer to a block of memory with a minimum size of size*nmemb bytes.
        //      size − This is the size in bytes of each element to be read.
        //      nmemb − This is the number of elements, each one with a size of size bytes.
        //      stream − This is the pointer to a FILE object that specifies an input stream.
        while (fread(&buffer, 512, 1, input_pointer) == 1)
        {
            printf("start yerr engines \n");
            // check for the start of a JPEG image
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                printf("Found a JPEG image\n");
                // if not the first JPEG
                if (!(i == 0))
                {
                    fclose(image_pointer);
                }
                // otherwise, write the file
                // Initialise file
                sprintf(filename, "%03i.jpg", i);
                image_pointer = fopen(filename, "w");
                i++;
            }
            else
            {
                printf("Not a JPEG image\n");
            }
            // if the jpeg has been found, write to file
            if (!(i == 0))
            {
                printf("Writing to file %s\n", filename);
                fwrite(&buffer, 512, 1, image_pointer); // thanks Tabnine
            }

            // Good practice to return 0
            return 0;
        }
        // Close to prevent memory leaks
        fclose(image_pointer);
        fclose(input_pointer);
    }
}