#include <stdio.h>

void printIP(int integer)
{
    int binaryArray[32];
    int byteArray[4] = {0, 0, 0, 0};
    int i;
    int j;
    int num = 1;
    for(i = 0; i < 32; i++)
    {
        binaryArray[i] = integer % 2;
        integer = integer / 2;
    }
    
    //printf("\n");
    //for(i = 0; i < 32; i++){printf("%d", binaryArray[i]);}
    //printf("\n");

    for(i = 0; i < 4; i++)
    {
        for(j = i * 8; j < ((i + 1) * 8); j++)
        {
            if(binaryArray[j] == 1)
            {
                byteArray[i] = byteArray[i] + num;
            }
            num = num * 2;
        }
        num = 1;
    }
    printf("%d.%d.%d.%d\n", byteArray[3], byteArray[2], byteArray[1], byteArray[0]);    
}

int reverseEndian(int integer)
{
    int hexArray[8];
    int hArray[8];
    int i;
    int j;
    int h = 0;
    int result = 0;
    int num = 1;
    for(i = 7; i > -1; i--)
    {
        hexArray[i] = integer % 16;
        integer = integer / 16;
    }
    //printf("\n");
    //for(i = 0; i < 8; i++){printf("%d", hexArray[i]);}
    //printf("\n");printf("\n");
    
    for(i = 7; i > -1; i -= 2)
    {
        for(j = i - 1; j < i + 1; j++)
        {
            hArray[h] = hexArray[j];
            h++;
        }
    }

    for(i = 7; i > -1; i--)
    {
        result = result + (hArray[i] * num);
        num = num * 16;
    }

    //printf("\n");
    //for(i = 0; i < 8; i++){printf("%d", hArray[i]);}
    //printf("\n");
    //printf("\n%d\n", result);

    return result;
}

int countGroups(int integer)
{
    int count = 0;
    int binaryArray[32];
    int i;
    int j;
    for(i = 0; i < 32; i++)
    {
        binaryArray[i] = 0;
    }
    for(i = 0; i < 32; i++)
    {
        j = integer >> i;
        if (j & 1)
        {
            binaryArray[i] = 1;
        }
        else
        {
            binaryArray[i] = 0;
        }
    }

    //printf("\n");
    //for(i = 0; i < 32; i++){printf("%d", binaryArray[i]);}
    //printf("\n");

    for(i = 0; i < 32; i++)
    {
        if(binaryArray[i] == 1)
        {
            j = i + 1;
            count++;
            while(j < 32 && binaryArray[j])
            {
                j++;
            }
            i = j;
         }
    }
    return count;
}
