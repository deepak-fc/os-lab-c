#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "Scheduling.h"

void executeProcess(Process* p, float currentTime, int timeQuantum)
{
    p->startingTime = currentTime;

    if (p->remainingBurst < timeQuantum)
        p->burst = p->remainingBurst;
    else
        p->burst = timeQuantum;

    updateValues(p);
    p->remainingBurst -= p->burst;

    if (p->remainingBurst <= 0)
        p->state = FINISHED;
}

void fcfs(Process* listProcess, int n)
{
    float currentTime = 0.0;
    int i = 0;
    sortById(listProcess, n);
    sortByArrivalTime(listProcess, n);

    while (i < n)
    {
        if (listProcess[i].arrivalTime > currentTime)
        {
            currentTime = listProcess[i].arrivalTime;
            continue;
        }
        executeProcess(&listProcess[i], currentTime, listProcess[i].burst);
        currentTime = listProcess[i].completionTime;
        i++;
    }
}

void sjf(Process* listProcess, int n)
{
    float currentTime = 0;
    int maxIndexForCurrentTime = 0;
    int i = 0;

    sortById(listProcess, n);
    sortByArrivalTime(listProcess, n);
    while (i < n)
    {
        for (int j = 0; j < n; j++)
            if (listProcess[j].arrivalTime <= currentTime && listProcess[j].state == IDLE)
                maxIndexForCurrentTime = j;

        sortByBurstTime(listProcess, maxIndexForCurrentTime + 1);

        if (listProcess[i].arrivalTime > currentTime)
        {
            currentTime = listProcess[i].arrivalTime;
            continue;
        }
        executeProcess(&listProcess[i], currentTime, listProcess[i].burst);
        currentTime = listProcess[i].completionTime;
        i++;
    }
}

Process* srtf(Process* listProcess, int n, int* newLength)
{
    Process* listProcessFinal = (Process*)calloc(1, sizeof(Process));
    processInit(&listProcessFinal[0]);
    int tempNewLength = 1;

    float currentTime = 0.0;
    int maxIndexForCurrentTime = 0;
    int i = 0;
    
    sortById(listProcess, n);
    sortByArrivalTime(listProcess, n);
    while (i < n)
    {
        for (int j = 0; j < n; j++)
            if (listProcess[j].arrivalTime <= currentTime && listProcess[j].state == IDLE)
                maxIndexForCurrentTime = j;

        sortByBurstTime(listProcess, maxIndexForCurrentTime + 1);

        if (listProcess[i].arrivalTime > currentTime)
        {
            currentTime = listProcess[i].arrivalTime;
            continue;
        }

        executeProcess(&listProcess[i], currentTime, 1);
        if (listProcessFinal[tempNewLength - 1].state != EMPTY)
        {
            if (listProcessFinal[tempNewLength - 1].id != listProcess[i].id)
            {
                listProcessFinal = (Process*)realloc(listProcessFinal, ++tempNewLength * sizeof(Process));
                listProcessFinal[tempNewLength - 1] = listProcess[i];
            }
            else
                listProcessFinal[tempNewLength - 1].completionTime = listProcess[i].completionTime;
        }
        else
            listProcessFinal[tempNewLength - 1] = listProcess[i];

        currentTime = listProcess[i].completionTime;
        if (listProcess[i].state == FINISHED)
            i++;
    }
    *newLength = tempNewLength;
    return listProcessFinal;
}

void priorityNonPreemptive(Process* listProcess, int n, bool priorityReversed)
{
    float currentTime = 0;
    int maxIndexForCurrentTime = 0;
    int i = 0;

    sortById(listProcess, n);
    sortByArrivalTime(listProcess, n);
    while (i < n)
    {
        for (int j = 0; j < n; j++)
            if (listProcess[j].arrivalTime <= currentTime && listProcess[j].state == IDLE)
                maxIndexForCurrentTime = j;

        sortByPriority(listProcess, maxIndexForCurrentTime + 1, priorityReversed);

        if (listProcess[i].arrivalTime > currentTime)
        {
            currentTime = listProcess[i].arrivalTime;
            continue;
        }
        executeProcess(&listProcess[i], currentTime, listProcess[i].burst);
        currentTime = listProcess[i].completionTime;
        i++;
    }
}

Process* priorityPreemptive(Process* listProcess, int n, bool priorityReversed, int *newLength)
{
    Process* listProcessFinal = (Process*)calloc(1, sizeof(Process));
    processInit(&listProcessFinal[0]);
    int tempNewLength = 1;

    float currentTime = 0.0;
    int maxIndexForCurrentTime = 0;
    int i = 0;

    sortById(listProcess, n);
    sortByArrivalTime(listProcess, n);
    while (i < n)
    {
        for (int j = 0; j < n; j++)
            if (listProcess[j].arrivalTime <= currentTime && listProcess[j].state == IDLE)
                maxIndexForCurrentTime = j;

        sortByPriority(listProcess, maxIndexForCurrentTime + 1, priorityReversed);

        if (listProcess[i].arrivalTime > currentTime)
        {
            currentTime = listProcess[i].arrivalTime;
            continue;
        }

        executeProcess(&listProcess[i], currentTime, 1);
        if (listProcessFinal[tempNewLength - 1].state != EMPTY)
        {
            if (listProcessFinal[tempNewLength - 1].id != listProcess[i].id)
            {
                listProcessFinal = (Process*)realloc(listProcessFinal, ++tempNewLength * sizeof(Process));
                listProcessFinal[tempNewLength - 1] = listProcess[i];
            }
            else
                listProcessFinal[tempNewLength - 1].completionTime = listProcess[i].completionTime;
        }
        else
            listProcessFinal[tempNewLength - 1] = listProcess[i];

        currentTime = listProcess[i].completionTime;
        if (listProcess[i].state == FINISHED)
            i++;
    }
    *newLength = tempNewLength;
    return listProcessFinal;
}

float averageWaitingTime(Process * listProcess, int n)
{
    float * waitingTimes = getAllWaitingTimes(listProcess, n);
    float average = sumOfFloatArray(waitingTimes,n) / n;
    free(waitingTimes);
    waitingTimes = NULL;
    return average;
}

float averageTurnaroundTime(Process * listProcess, int n)
{
    float * turnaroundTimes = getAllTurnaroundTimes(listProcess, n);
    float average = sumOfFloatArray(turnaroundTimes,n) / n; 
    free(turnaroundTimes);
    turnaroundTimes = NULL;
    return average;
}

void displayGantt(Process * listProcess, int n)
{
    int i = 0;
    float interval = 0.0;

    while (i < n)
    {
        if(listProcess[i].startingTime > interval)
        {
            printf("IDLE\t|");
            interval = listProcess[i].startingTime;
        }
        else
        {
            printf("P%-5d\t|", listProcess[i].id);
            interval = listProcess[i].completionTime;
            i++;
        }
    }
    printf("\n");
    
    interval = 0.0;
    i = 0;
    printf("0.0\t");
    while(i<n)
    {
        if(interval < listProcess[i].startingTime)
            interval = listProcess[i].startingTime;
        else
        {
            interval = listProcess[i].completionTime;
            i++;
        }
        printf("%-3.1f\t", interval);
    }
    printf("\n");
}