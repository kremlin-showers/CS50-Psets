#include "helpers.h"
#include "math.h"
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
// looping over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
// taking RGB values of each pixel
            BYTE r = image[i][j].rgbtRed;
            BYTE g = image[i][j].rgbtGreen;
            BYTE b = image[i][j].rgbtBlue;
// taking average of said values
            BYTE x = round((r + g + b) / (float)3);

//setting Red Green and blue equal to the average
            image[i][j].rgbtRed = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtBlue = x;
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
            RGBTRIPLE x = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = x;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
// creating a temporary array
    RGBTRIPLE temparray[height][width];
// creating ints for storing the sum of RGB values of the block of 9 pixels
    int redsum = 0;
    int greensum = 0;
    int bluesum = 0;
    float count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redsum = 0;
            greensum = 0;
            bluesum = 0;
            count = 0;
// looping over the 3X3 block around our centre pixel
            for (int x = i - 1; x < i + 2; x++)
            {
                for (int y = j - 1; y < j + 2; y++)
                {
// checking if image[x][y] exists
                    if (x  >= 0 && x < height && y >= 0 && y < width)
                    {
// adding RGB values of image[x][y] to the sums
                        redsum += image[x][y].rgbtRed;
                        greensum += image[x][y].rgbtGreen;
                        bluesum += image[x][y].rgbtBlue;
                        count++;
                    }
                }
            }
// taking the average of the RGB values
            BYTE red = round(redsum / count);
            BYTE green = round(greensum / count);
            BYTE blue = round(bluesum / count);
            temparray[i][j].rgbtBlue = blue;
            temparray[i][j].rgbtGreen = green;
            temparray[i][j].rgbtRed = red;
        }

    }
// setting the image equal to the temparray
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temparray[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
// storing values
    float redy;
    float greeny;
    float bluey;
    float redx;
    float greenx;
    float bluex;
// array full of modifing weights
    int modx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int mody[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redy = 0.000;
            greeny = 0.000;
            bluey = 0.000;
            redx = 0.000;
            bluex = 0.000;
            greenx = 0.000;
            for (int k = -1; k < 2; k++)
            {
                if (i + k > height - 1 || i + k < 0)
                {
                    continue;
                }
                for (int l = -1; l < 2; l++)
                {
                    if (j + l > width - 1 || j + l < 0)
                    {
                        continue;
                    }
                    int modifier = (k + 1) * 3 + l + 1;
                    int modifierx = modx[modifier];
                    int modifiery = mody[modifier];

                    RGBTRIPLE a = image[i + k][j + l];
                    redy += a.rgbtRed * modifiery;
                    greeny += a.rgbtGreen * modifiery;
                    bluey += a.rgbtBlue * modifiery;
                    redx += a.rgbtRed * modifierx;
                    bluex += a.rgbtBlue * modifierx;
                    greenx += a.rgbtGreen * modifierx;
                }
            }
            BYTE Red = fmin(round(sqrt(redx * redx + redy * redy)), 255);
            BYTE Green = fmin(round(sqrt(greenx * greenx + greeny * greeny)), 255);
            BYTE Blue = fmin(round(sqrt(bluex * bluex + bluey * bluey)), 255);
            temp[i][j].rgbtBlue = Blue;
            temp[i][j].rgbtGreen = Green;
            temp[i][j].rgbtRed = Red;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}