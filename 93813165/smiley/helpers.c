#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Defining  the color you want to use
    RGBTRIPLE color;
    color.rgbtRed = 0;    // Red component
    color.rgbtGreen = 0;  // Green component
    color.rgbtBlue = 255; // blue color

    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)

            {

                image[i][j] = color;
            }
        }
    }
}
