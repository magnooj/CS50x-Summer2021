#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int avg = round((float)(image[row][col].rgbtBlue + image[row][col].rgbtRed + image[row][col].rgbtGreen) / 3);

            image[row][col].rgbtBlue = avg;
            image[row][col].rgbtRed = avg;
            image[row][col].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sepiaRed = round(.393 * image[row][col].rgbtRed + .769 * image[row][col].rgbtGreen + .189 * image[row][col].rgbtBlue);
            int sepiaGreen = round(.349 * image[row][col].rgbtRed + .686 * image[row][col].rgbtGreen + .168 * image[row][col].rgbtBlue);
            int sepiaBlue = round(.272 * image[row][col].rgbtRed + .534 * image[row][col].rgbtGreen + .131 * image[row][col].rgbtBlue);

            // checking if they are more than 255
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
            // reasigning new colors
            image[row][col].rgbtBlue = sepiaBlue;
            image[row][col].rgbtRed = sepiaRed;
            image[row][col].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        //deviding width by 2 because of preventing to copy again
        for (int col = 0; col < (width / 2); col++)
        {
            RGBTRIPLE imageinfo = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - col - 1] = imageinfo;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a room for copying the image
    RGBTRIPLE nimage[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Sum variable of the colors
            int sBlue = 0;
            int sGreen = 0;
            int sRed = 0;
            float counter = 0.00;

            // near row and column from -1 to +1
            for (int nrow = -1; nrow <= 1; nrow++)
            {
                for (int ncol = -1; ncol <= 1; ncol++)
                {
                    // If they are not empty
                    if (row + nrow < 0 || row + nrow > height - 1 || col + ncol < 0 || col + ncol > width - 1)
                    {
                        continue;
                    }
                    sBlue += image[row + nrow][col + ncol].rgbtBlue;
                    sRed += image[row + nrow][col + ncol].rgbtRed;
                    sGreen += image[row + nrow][col + ncol].rgbtGreen;

                    counter++;
                }
            }
            // Calculating new colors in image copy
            nimage[row][col].rgbtBlue = round(sBlue / counter);
            nimage[row][col].rgbtRed = round(sRed / counter);
            nimage[row][col].rgbtGreen = round(sGreen / counter);
        }
    }
    // reasigning new colors
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col].rgbtBlue = nimage[row][col].rgbtBlue;
            image[row][col].rgbtRed = nimage[row][col].rgbtRed;
            image[row][col].rgbtGreen = nimage[row][col].rgbtGreen;
        }
    }
    return;
}
