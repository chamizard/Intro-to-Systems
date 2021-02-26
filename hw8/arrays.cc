#include <stdio.h>

double getPositiveAverage(double myArray[], int numItems)
{
    double avg = 0;
    int count = 1;
    int index = 0;
    while (count < numItems + 1)
    {
        if (myArray[index] > 0)
        {
            avg = avg + myArray[index];
            count++;
        }
        else
        {
            numItems--;
        }
        index++;
    }
    return (avg / ((double)numItems));
}

int countRangeValues(double myArray[], int numItems, double countVal)
{
    double upper = countVal + 0.5;
    double lower = countVal - 0.5;
    int count = 0;
    int i;
    for (i = 0; i < numItems; i++) 
    {
        if (myArray[i] < upper && myArray[i] >= lower)
        {
            count++;
        }
    }
    return count;
}

double getMaxAbsolute(double myArray[], int numItems)
{
    int index = 0;
    int i;
    double highVal = myArray[0];
    if (highVal < 0)
    {
        highVal = highVal * -1;
    }
    for(i = 0; i < numItems; i++)
    {
        if(myArray[i] < 0)
        {
            myArray[i] = myArray[i] * -1;
            if(myArray[i] > highVal)
            {
                highVal = myArray[i];
                index = i;
            }
            myArray[i] = myArray[i] * -1;
        }
        else if(myArray[i] > highVal)
        {
            highVal = myArray[i];
            index = i;
        }
        else if(myArray[i] == highVal)
        {
            highVal = myArray[i];
            index = i;
        }
    }
    return myArray[index];
}

int countInverses(int myArray[], int numItems)
{
    int i;
    int j;
    int count = 0;
    for(i = 0; i < numItems; i++)
    {
        for(j = 1; j < numItems; j++)
        {
            if(myArray[i] != 0 && myArray[j] != 0)
            {
                if(myArray[i] * -1 == myArray[j] || myArray[j] * -1 == myArray[i])
                {
                    myArray[i] = 0;
                    myArray[j] = 0;
                    count ++;
                }
            }
        }
    }
    return count;
}

int getMaxCount(double myArray[], int numItems)
{
    double * ptr;
    ptr = myArray;
    double max = getMaxAbsolute(ptr, numItems);
    int count = countRangeValues(ptr, numItems, max);
    return count;
}
