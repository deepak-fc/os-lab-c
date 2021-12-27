#define _CRT_SECURE_NO_WARNINGS

#include "Utilities.h"
#include <stdlib.h>

void clearScreen()
{
    system("tput reset||clear||cls");
}

float sumOfFloatArray(float arrayFloat[], int n)
{
    float sum = 0;
    for(int i=0;i<n;i++)
        sum += arrayFloat[i];
    return sum;
}

float sumOfIntArray(float arrayInt[],int n)
{
    int sum = 0;
    for(int i=0;i<n;i++)
        sum += arrayInt[i];
    return sum;
}