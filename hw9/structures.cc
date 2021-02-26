//Cameron Mann
//Programming Assignment 3 - Structures
#include <stdio.h>
#include <string.h>
#include "structures.h"

void getOneDVD(dvd_t *dvd)
{
    printf("Enter title: ");
    char input[81];
    scanf("%80[^\n]s", input);
    char c;
    scanf("%c", &c);
    strncpy(dvd->title, input, 80);

    printf("Enter director: ");
    char in[81];
    scanf("%80[^\n]s", in);
    char d;
    scanf("%c", &d);
    strncpy(dvd->director, in, 80);

    int num;
    printf("Enter play time in minutes: ");
    scanf("%d", &num);
    dvd->playTime = num;
    char e;
    scanf("%c", &e); 
}

void printOneDVD(dvd_t dvd)
{
    printf("%s:%s:%d\n", dvd.title, dvd.director, dvd.playTime);
}

void getCollection(dvd_t collection[], int numDVD)
{
    int i;
    for(i = 0; i < numDVD; i++)
    {
        getOneDVD(&collection[i]);
    }
}

void printCollection(dvd_t collection[], int numDVD)
{
    int i;
    for(i = 0; i < numDVD; i++)
    {
        printOneDVD(collection[i]);
    }
}
