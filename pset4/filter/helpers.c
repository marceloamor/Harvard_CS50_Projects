#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];

            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create temporary array of pixels to blur
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //create and initalise intermediary values
            float blue_sum;
            float green_sum;
            float red_sum;

            float counter;

            blue_sum = green_sum = red_sum = counter = 0;

            //calculate sums for pixels in middle of image
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                blue_sum += temp[i + 1][j + 1].rgbtBlue;
                green_sum += temp[i + 1][j + 1].rgbtGreen;
                red_sum += temp[i + 1][j + 1].rgbtRed;
                counter ++;
            }

            //handle edge cases with if statements
            //corner pixels
            //top left
            if (i - 1 >= 0 && j >= 0)
            {
                blue_sum += temp[i - 1][j].rgbtBlue;
                green_sum += temp[i - 1][j].rgbtGreen;
                red_sum += temp[i - 1][j].rgbtRed;
                counter ++;
            }
            //
            //top right
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                blue_sum += temp[i - 1][j - 1].rgbtBlue;
                green_sum += temp[i - 1][j - 1].rgbtGreen;
                red_sum += temp[i - 1][j - 1].rgbtRed;
                counter ++;
            }
            //bottom left
            if (i >= 0 && j - 1 >= 0)
            {
                blue_sum += temp[i][j - 1].rgbtBlue;
                green_sum += temp[i][j - 1].rgbtGreen;
                red_sum += temp[i][j - 1].rgbtRed;
                counter ++;
            }
            //bottom right
            if (i >= 0 && j >= 0)
            {
                blue_sum += temp[i][j].rgbtBlue;
                green_sum += temp[i][j].rgbtGreen;
                red_sum += temp[i][j].rgbtRed;
                counter ++;
            }

            //edge pixels, non-corner
            //left edges
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                blue_sum += temp[i + 1][j].rgbtBlue;
                green_sum += temp[i + 1][j].rgbtGreen;
                red_sum += temp[i + 1][j].rgbtRed;
                counter ++;
            }
            //right edges
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                blue_sum += temp[i + 1][j - 1].rgbtBlue;
                green_sum += temp[i + 1][j - 1].rgbtGreen;
                red_sum += temp[i + 1][j - 1].rgbtRed;
                counter ++;
            }
            //top edges
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                blue_sum += temp[i - 1][j + 1].rgbtBlue;
                green_sum += temp[i - 1][j + 1].rgbtGreen;
                red_sum += temp[i - 1][j + 1].rgbtRed;
                counter ++;
            }
            //bottom edges
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                blue_sum += temp[i][j + 1].rgbtBlue;
                green_sum += temp[i][j + 1].rgbtGreen;
                red_sum += temp[i][j + 1].rgbtRed;
                counter ++;
            }


            //finalise image array with calculated values
            image[i][j].rgbtBlue = round(blue_sum / counter);
            image[i][j].rgbtGreen = round(green_sum / counter);
            image[i][j].rgbtRed = round(red_sum / counter);

        }
    }
    return;
}

// Detects and highlights edges using Sobel algorithm
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //create temp array
    RGBTRIPLE temp[height][width];

    //initalise Sober kernel arrays
    int gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //loop through image height and width
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //initialise gx and gy values
            int gxBlue = 0;
            int gxGreen = 0;
            int gxRed = 0;

            int gyBlue = 0;
            int gyGreen = 0;
            int gyRed = 0;

            //loop through sobel array
            for (int i = -1; i < 2; i ++)
            {
                for (int j = -1; j < 2; j++)
                {
                    //handle edge cases
                    if (h + i < 0 || h + i >= height)
                    {
                        continue; //skip
                    }
                    if (w + j < 0 || w + j >= width)
                    {
                        continue; //skip
                    }

                    //run image through Sober kernels
                    gxBlue += image[h + i][w + j].rgbtBlue * gx[i + 1][j + 1];
                    gxGreen += image[h + i][w + j].rgbtGreen * gx[i + 1][j + 1];
                    gxRed += image[h + i][w + j].rgbtRed * gx[i + 1][j + 1];

                    gyBlue += image[h + i][w + j].rgbtBlue * gy[i + 1][j + 1];
                    gyGreen += image[h + i][w + j].rgbtGreen * gy[i + 1][j + 1];
                    gyRed += image[h + i][w + j].rgbtRed * gy[i + 1][j + 1];

                }
            }

            //calculate final Sobel values using Sobel equation
            int blueSobel = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
            int greenSobel = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
            int redSobel = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));

            //cap values at 255
            if (blueSobel > 255)
            {
                blueSobel = 255;
            }
            if (greenSobel > 255)
            {
                greenSobel = 255;
            }
            if (redSobel > 255)
            {
                redSobel = 255;
            }

            //set temp values to Sobel values
            temp[h][w].rgbtBlue = blueSobel;
            temp[h][w].rgbtGreen = greenSobel;
            temp[h][w].rgbtRed = redSobel;

        }
    }

    //set final image to temp values calculated
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
        }
    }

    return;
}