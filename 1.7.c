/*
 Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4
 bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
 */

#include <stdio.h>

int *at(int *matrix, int n, int r, int c)
{
    return &matrix[r * n + c];
}

int *rightAt(int *matrix, int n, int r, int c)
{
    return &matrix[c * n + (n - r - 1)];
}

int *mirrorAt(int *matrix, int n, int r, int c)
{
    return &matrix[(n - r - 1) * n + (n - c - 1)];
}

int *bottomAt(int *matrix, int n, int r, int c)
{
    return &matrix[(n - c - 1) * n  + r];
}

void rotateMatrix(int *matrix, int n)
{
    if (n < 2)
        return;

    for (int row = 0; row < n / 2; ++row)
    {
        const int C = n - row - 1;
        for (int col = row; col < C; ++col)
        {
            int *c11 = at(matrix, n, row, col);
            int *c12 = rightAt(matrix, n, row, col);
            int *c21 = bottomAt(matrix, n, row, col);
            int *c22 = mirrorAt(matrix, n, row, col);
            int leftTop = *c11;
            *c11 = *c21;
            *c21 = *c22;
            *c22 = *c12;
            *c12 = leftTop;
            
        }
    }
}

void print(int *matrix, int n)
{
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            if (col == 0)
                printf("%d", *at(matrix, n, row, col));
            else
                printf(", %d", *at(matrix, n, row, col));
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    int matrix[49] =
    {
        11, 12, 13, 14, 15, 16, 17,
        21, 22, 23, 24, 25, 26, 27,
        31, 32, 33, 34, 35, 36, 37,
        41, 42, 43, 44, 45, 46, 47,
        51, 52, 53, 54, 55, 56, 57,
        61, 62, 63, 64, 65, 66, 67,
        71, 72, 73, 74, 75, 76, 77
    };

    rotateMatrix(matrix, 7);
    print(matrix, 7);
    return 0;
}