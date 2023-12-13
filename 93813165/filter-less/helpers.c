#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
//iterage over each image outer row
  for(int i = 0; i<height; i++)
  {
    //iterate over the image inner row
    for ( int j = 0; j < width ; j++)
    {
      // Calculate the grayscale value (average of red, green, and blue)
            BYTE average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Set the grayscale value for all channels
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;



    }
  }
     return;


}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
   //iterage over each image outer row
  for(int i = 0; i<height; i++)
  {
    //iterate over the image inner row
    for ( int j = 0; j < width ; j++)
    {
      // Calculate the sepia using the giving formular
          int sepiaRed =round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
          int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
          int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 *image[i][j].rgbtBlue);

      // Set the grayscale value for all channels
          image[i][j].rgbtBlue = sepiaBlue <= 255 ? sepiaBlue: 255;
          image[i][j].rgbtGreen = sepiaGreen <=255 ? sepiaGreen :255;
          image[i][j].rgbtRed = sepiaRed <=255 ? sepiaRed:255;



    }
  }
     return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
    {
        // Iterate over each row
        int start = 0;
        int end = width - 1;

        while (start < end)
        {
            // Swap the pixels (left and right)
            RGBTRIPLE temp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = temp;

            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary image to store the blurred result
    RGBTRIPLE temp[height][width];

    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // Iterate over neighboring pixels (3x3 kernel)
            for (int ni = -1; ni <= 1; ni++)
            {
                for (int nj = -1; nj <= 1; nj++)
                {
                    int ni_new = i + ni;
                    int nj_new = j + nj;

                    // Check if the neighbor is within the image bounds
                    if (ni_new >= 0 && ni_new < height && nj_new >= 0 && nj_new < width)
                    {
                        // Accumulate color values from neighboring pixels
                        sumRed += image[ni_new][nj_new].rgbtRed;
                        sumGreen += image[ni_new][nj_new].rgbtGreen;
                        sumBlue += image[ni_new][nj_new].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color value
            temp[i][j].rgbtRed = round((float)sumRed / count);
            temp[i][j].rgbtGreen = round((float)sumGreen / count);
            temp[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }

    // Copy the blurred image from temp back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
