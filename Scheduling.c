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

void nonPreemptiveScheduler(Process * listProcess, int n, AlgoName algoName, bool reverseSort)
{
    float currentTime = 0.0;
    int i = 0;
    int maxIndexForCurrentTime = 0;
    
    sortProcessListBy(listProcess, n, ID, false);
    sortProcessListBy(listProcess, n, ARRIVAL, false);

    while (i < n)
    {
        for (int j = 0; j < n; j++)
            if (listProcess[j].arrivalTime <= currentTime && listProcess[j].state == IDLE)
                maxIndexForCurrentTime = j;

        switch (algoName)
        {
            case FCFS:
                break;
            case SJF:
                sortProcessListBy(listProcess, maxIndexForCurrentTime + 1, BURST, false);
                break;
            case PRIORITY_NON_PREEMPTIVE:
                sortProcessListBy(listProcess, maxIndexForCurrentTime + 1, PRIORITY, reverseSort);
                break;
            default:
                printf("\n[ERROR] Invalid algo name passed to scheduler function\n");
                return;
        }
        
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

Process* preemptiveScheduler(Process* listProcess, int n, AlgoName algoName, bool reverseSort, int * newLength)
{
    Process* ganttList = (Process*)calloc(1, sizeof(Process));
    processInit(&ganttList[0]);
    int tempNewLength = 1;
    
    float currentTime = 0.0;
    int maxIndexForCurrentTime = 0;
    int i = 0;
    
    sortProcessListBy(listProcess, n, ID, false);
    sortProcessListBy(listProcess, n, ARRIVAL, false);
    
    while (i < n)
    {
        for (int j = 0; j < n; j++)
            if (listProcess[j].arrivalTime <= currentTime && listProcess[j].state == IDLE)
                maxIndexForCurrentTime = j;
    
        switch (algoName)
        {
            case SRTF:
                sortProcessListBy(listProcess, maxIndexForCurrentTime + 1, BURST, false);
                break;
            case PRIORITY_PREEMPTIVE:
                sortProcessListBy(listProcess, maxIndexForCurrentTime + 1, PRIORITY, reverseSort);
                break;
            default:
                printf("\n[ERROR] Invalid algo name passed to scheduler function\n");
                return;
        }

        if (listProcess[i].arrivalTime > currentTime)
        {
            currentTime = listProcess[i].arrivalTime;
            continue;
        }
    
        executeProcess(&listProcess[i], currentTime, 1);
        
        if (ganttList[tempNewLength - 1].state != EMPTY)
        {
            if (ganttList[tempNewLength - 1].id != listProcess[i].id)
            {
                ganttList = (Process*)realloc(ganttList, ++tempNewLength * sizeof(Process));
                ganttList[tempNewLength - 1] = listProcess[i];
            }
            else
                ganttList[tempNewLength - 1].completionTime = listProcess[i].completionTime;
        }
        else
            ganttList[tempNewLength - 1] = listProcess[i];
    
        currentTime = listProcess[i].completionTime;
        if (listProcess[i].state == FINISHED)
            i++;
    }
    *newLength = tempNewLength;
    return ganttList;
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
    int idleProcessCount = 0;
    
    while (i < n)
    {
        if (listProcess[i].startingTime > interval)
        {
            interval = listProcess[i].startingTime;
            idleProcessCount++;
        }
        else
        {
            interval = listProcess[i].completionTime;
            i++;
        }
    }

    interval = 0.0;
    i = 0;

    printf("\n\nGANTT CHART\n");
    drawLine((idleProcessCount + n)* 8);
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
    drawLine((idleProcessCount + n) * 8);
    
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