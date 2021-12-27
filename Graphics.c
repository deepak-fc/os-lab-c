#include <stdio.h>
#include "Graphics.h"

void drawLine(int length)
{
    int i;
    for(i=0; i<length; i++)
    {
        printf("-");
    }
    printf("\n");
}