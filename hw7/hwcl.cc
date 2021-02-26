#include <stdio.h>

void printRectangleWhile(int width, int height)
{
    char plus = '+';
    char minus = '-';
    int rowCount = height;
    int colCount = width;
    if(width > 1 && height > 1)
    {
        while(rowCount > 0)
        {
            while(colCount > 0)
            {
                if(height == rowCount || rowCount == 1)
                {
                    printf("%c",plus);
                }
                else if(colCount == width || colCount == 1)
                {
                    printf("%c",plus);
                }
                else
                {
                    printf("%c",minus);
                }
                if(colCount == 1)
                {
                    printf("%n\n");
                }
                colCount--;
            }
            colCount = width;
            rowCount--;
        }
    }
}

void printTriangleFor(int height)
{
    char plus = '+';
    char minus = '-';
    char space = ' ';
    int rowCount;
    int colCount;
    for(rowCount = 1;rowCount < height + 1; rowCount++)
    {
        for(colCount = 0;colCount < height; colCount++)
        {
            if(colCount == height - rowCount || colCount == height - 1 || rowCount == height)
            {
                printf("%c",plus);
            }
            else if(rowCount >= 3 && colCount > height - rowCount)
            {
                printf("%c",minus);
            }
            else
            {
                printf("%c",space);
            }
        }
        printf("%n\n");
    }
}

