#include "helpers.h"
// hints says to round so we'll use math.h
#include <math.h>

// why do i feel like this is going to be a lot of for-loops

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // do stuff
            // make sure RGB are all the same value
            // average for the brightness of grey relative to RGB
            // apply to each pixel
            // using BMP.h
            // divide by three to get the average
            int average = round((image[x][y].rgbtRed + image[x][y].rgbtGreen + image[x][y].rgbtBlue) / 3);
            image[x][y].rgbtRed = average;
            image[x][y].rgbtGreen = average;
            image[x][y].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // from problemt notes
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // do stuff
            int sepiaRed = round((0.393 * image[x][y].rgbtRed) + (0.769 * image[x][y].rgbtGreen) + (0.189 * image[x][y].rgbtBlue));
            int sepiaGreen = round((0.349 * image[x][y].rgbtRed) + (0.686 * image[x][y].rgbtGreen) + (0.168 * image[x][y].rgbtBlue));
            int sepiaBlue = round((0.272 * image[x][y].rgbtRed) + (0.534 * image[x][y].rgbtGreen) + (0.131 * image[x][y].rgbtBlue));
            // gotta make sure its less than 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // actually set the values now
            image[x][y].rgbtRed = sepiaRed;
            image[x][y].rgbtGreen = sepiaGreen;
            image[x][y].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // going to need to have temporary values
    // lecture wine glass problem
    typedef struct
    {
        BYTE rgbtRed;
        BYTE rgbtGreen;
        BYTE rgbtBlue;
    } temporary;

    temporary temporaryImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // do stuff
            // Red
            temporaryImage[i][j].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temporaryImage[i][j].rgbtRed;
            // Green
            temporaryImage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temporaryImage[i][j].rgbtGreen;
            // Blue
            temporaryImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temporaryImage[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // going to need to have temporary values (work non-destructively, preserve original image)
    // lecture wine glass problem (shortening)
    typedef struct
    {
        BYTE rgbtRed;
        BYTE rgbtGreen;
        BYTE rgbtBlue;
    } temp;

    temp tempimage[height][width];

    // make a copy of the original image
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            tempimage[a][b].rgbtRed = image[a][b].rgbtRed;
            tempimage[a][b].rgbtBlue = image[a][b].rgbtBlue;
            tempimage[a][b].rgbtGreen = image[a][b].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // do stuff
            // event handling for whole image, cant sample nine if you're touching less than that
            // goes clockwise from top left corner
            //
            // first line and left corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i +
                                              1][j + 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i + 1][j].rgbtGreen +
                                                tempimage[i + 1][j + 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i + 1][j].rgbtBlue + tempimage[i
                                               + 1][j + 1].rgbtBlue) / 4.0));
            }
            // first line and right corner
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i + 1][j - 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i + 1][j].rgbtGreen + tempimage[i + 1][j - 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i + 1][j].rgbtBlue + tempimage[i + 1][j - 1].rgbtBlue) / 4.0));
            }
            // last line and left corner
            else if (j == 0 && i == height - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i - 1][j + 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i - 1][j + 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i - 1][j + 1].rgbtBlue) / 4.0));
            }
            // last line and right corner
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i - 1][j - 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i - 1][j - 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i - 1][j - 1].rgbtBlue) / 4.0));
            }
            // top edge
            else if (i == 0)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i + 1][j - 1].rgbtRed  + tempimage[i + 1][j + 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i + 1][j].rgbtGreen + tempimage[i + 1][j - 1].rgbtGreen  + tempimage[i + 1][j + 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i+ 1][j].rgbtBlue + tempimage[i + 1][j - 1].rgbtBlue  + tempimage[i + 1][j + 1].rgbtBlue) / 6.0));
            }
            // bottom edge
            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i - 1][j - 1].rgbtRed  + tempimage[i - 1][j + 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i - 1][j - 1].rgbtGreen  + tempimage[i - 1][j + 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i - 1][j - 1].rgbtBlue  + tempimage[i - 1][j + 1].rgbtBlue) / 6.0));
            }
            // left edge
            else if (j == 0)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i - 1][j + 1].rgbtRed  + tempimage[i + 1][j + 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i + 1][j].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i - 1][j + 1].rgbtGreen  + tempimage[i + 1][j + 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i + 1][j].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i - 1][j + 1].rgbtBlue  + tempimage[i + 1][j + 1].rgbtBlue) / 6.0));
            }
            // right edge
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i - 1][j - 1].rgbtRed  + tempimage[i + 1][j - 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i + 1][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i - 1][j - 1].rgbtGreen  + tempimage[i + 1][j - 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i + 1][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i - 1][j - 1].rgbtBlue  + tempimage[i + 1][j - 1].rgbtBlue) / 6.0));
            }
            // otherwise, average all
            else
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i - 1][j - 1].rgbtRed  + tempimage[i - 1][j + 1].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i + 1][j + 1].rgbtRed + tempimage[i + 1][j - 1].rgbtRed) / 9.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i - 1][j - 1].rgbtGreen  + tempimage[i - 1][j + 1].rgbtGreen + tempimage[i + 1][j].rgbtGreen + tempimage[i + 1][j + 1].rgbtGreen + tempimage[i + 1][j - 1].rgbtGreen) / 9.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i - 1][j - 1].rgbtBlue  + tempimage[i - 1][j + 1].rgbtBlue + tempimage[i + 1][j].rgbtBlue + tempimage[i + 1][j + 1].rgbtBlue + tempimage[i + 1][j - 1].rgbtBlue) / 9.0));
            }

        }
    }
    return;
}
