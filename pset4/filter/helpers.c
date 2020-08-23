#include "helpers.h"
#include <math.h>
#include <stdbool.h>


int cap(int n);
void swap(RGBTRIPLE *a, RGBTRIPLE *b);
bool isValid(int i, int j, int height, int width);
RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width]);
RGBTRIPLE get_edged_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;

            image[i][j].rgbtRed = cap(round(sum / 3.0));
            image[i][j].rgbtGreen = cap(round(sum / 3.0));
            image[i][j].rgbtBlue = cap(round(sum / 3.0));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width/2; j++, k--)
        {
            swap(&image[i][j], &image[i][k]);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            temp[i][j] = get_blurred_pixel(i, j, height, width, image);
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            temp[i][j] = get_edged_pixel(i, j, height, width, image);
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

int cap(int n)
{
    return n > 255 ? 255 : n;
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

bool isValid(int i, int j, int height, int width)
{
    return ((i >= 0) && (i < height)) && ((j >= 0) && (j < width));
}

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int sumRed, sumGreen, sumBlue, counter;
    sumRed = sumGreen = sumBlue = counter = 0;

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (isValid(i + di, j + dj, height, width))
            {
                sumRed += image[i + di][j + dj].rgbtRed;
                sumGreen += image[i + di][j + dj].rgbtGreen;
                sumBlue += image[i + di][j + dj].rgbtBlue;
                counter++;
            }
        }
    }

    RGBTRIPLE pixel;
    pixel.rgbtRed = cap(round((float) sumRed / counter));
    pixel.rgbtGreen = cap(round((float) sumGreen / counter));
    pixel.rgbtBlue = cap(round((float) sumBlue / counter));
    return pixel;
}

RGBTRIPLE get_edged_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int Gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int GxRed, GxGreen, GxBlue, GyRed, GyGreen, GyBlue;
    GxRed = GxGreen = GxBlue = GyRed = GyGreen = GyBlue = 0;

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (isValid(i + di, j + dj, height, width))
            {
                GxRed += Gx_kernel[di + 1][dj + 1] * image[i + di][j + dj].rgbtRed;
                GxGreen += Gx_kernel[di + 1][dj + 1] * image[i + di][j + dj].rgbtGreen;
                GxBlue += Gx_kernel[di + 1][dj + 1] * image[i + di][j + dj].rgbtBlue;

                GyRed += Gy_kernel[di + 1][dj + 1] * image[i + di][j + dj].rgbtRed;
                GyGreen += Gy_kernel[di + 1][dj + 1] * image[i + di][j + dj].rgbtGreen;
                GyBlue += Gy_kernel[di + 1][dj + 1] * image[i + di][j + dj].rgbtBlue;
            }
        }
    }

    RGBTRIPLE pixel;
    pixel.rgbtRed = cap(round(sqrt(GxRed*GxRed + GyRed*GyRed)));
    pixel.rgbtGreen = cap(round(sqrt(GxGreen*GxGreen + GyGreen*GyGreen)));
    pixel.rgbtBlue = cap(round(sqrt(GxBlue*GxBlue + GyBlue*GyBlue)));
    return pixel;
}