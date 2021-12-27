#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "Process.h"

void processInit(Process * p)
{
    p->id = 0;
    p->priority = 0;
    p->initialBurst = 0;
    p->burst = 0;
    p->remainingBurst = 0;
    p->arrivalTime = 0;
    p->turnaroundTime = 0;
    p->waitingTime = 0;
    p->initialStartingTime = 0;
    p->startingTime = 0;
    p->completionTime = 0;
    p->responseTime = 0;
    p->state = EMPTY;
}

void updateValues(Process * p)
{   
    if (p->completionTime == 0)
        p->initialStartingTime = p->startingTime;

    if(p->state != FINISHED)
        p->completionTime = p->startingTime + p->burst;
    
    p->turnaroundTime = p->completionTime - p->arrivalTime;
    p->waitingTime = p->turnaroundTime - p->burst;
    p->responseTime = p->startingTime - p->arrivalTime;
}

void displayProcess(Process * p)
{
    p->startingTime = p->initialStartingTime;
    p->burst = p->initialBurst;
    updateValues(p);
    printf("%-5d\t|%-8d\t|%-5d\t|%-5.1f\t|%-5.1f\t|%-5.1f\t|%-5.1f\t|%-5.1f\t|%-5.1f\t|\n", p->id, p->priority, p->burst, p->arrivalTime,
     p->turnaroundTime, p->waitingTime, p->startingTime, p->completionTime, p->responseTime);
}

void displayProcesses(Process listProcess[], int len)
{
    int i=0;
    drawLine(81);
    printf("PID\t|Priority\t|B.T\t|A.T\t|TAT\t|W.T\t|S.T\t|C.T\t|R.T\t|\n");
    drawLine(81);
    for(i=0; i<len; i++)
        displayProcess(&listProcess[i]);
    drawLine(81);
}

void swapProcess(Process * a, Process * b)
{
    Process c;
    c = *a;
    *a = *b;
    *b = c;
}

void processGetUserInput(Process * p)
{
    printf("Enter Process ID: ");
    scanf("%d", &p->id);
    printf("Enter Burst Time: ");
    scanf("%d", &p->burst);
    p->initialBurst = p->burst;
    p->remainingBurst = p->burst;
    printf("Enter Arrival Time: ");
    scanf("%f", &p->arrivalTime);
    printf("Enter Priority: ");
    scanf("%d", &p->priority);
    p->state = IDLE;
    drawLine(80);
}

void sortByArrivalTime(Process * listProcess, int n)
{
    int i = 0;
    int j = 0;
    bool sorted;
    for(i=0; i<n-1; i++)
    {
        sorted = true;
        for(j=0; j<n-1; j++)
        {
            if(listProcess[j].state == FINISHED)
                continue;

            else if(listProcess[j + 1].arrivalTime < listProcess[j].arrivalTime)           
            {
                swapProcess(&listProcess[j+1], &listProcess[j]);
                sorted = false;
            }
        }   

        if(sorted == true)
            return;
    }
}

void sortByBurstTime(Process * listProcess, int n)
{
    int i = 0;
    int j = 0;
    bool sorted;
    for(i=0; i<n-1; i++)
    {
        sorted = true;
        for(j=0; j<n-1; j++)
        {
            if(listProcess[j].state == FINISHED)
                continue;

            else if(listProcess[j + 1].remainingBurst < listProcess[j].remainingBurst)           
            {
                swapProcess(&listProcess[j+1], &listProcess[j]);
                sorted = false;
            }
        }   

        if(sorted == true)
            return;
    }
}

void sortByPriority(Process* listProcess, int n, bool priorityReverse)
{
    int i = 0;
    int j = 0;
    bool sorted;
    for (i = 0; i < n - 1; i++)
    {
        sorted = true;
        for (j = 0; j < n - 1; j++)
        {
            if (listProcess[j].state == FINISHED)
                continue;

            else if (listProcess[j + 1].priority < listProcess[j].priority && priorityReverse == false)
            {
                swapProcess(&listProcess[j + 1], &listProcess[j]);
                sorted = false;
            }
            else if (listProcess[j + 1].priority > listProcess[j].priority && priorityReverse == true)
            {
                swapProcess(&listProcess[j + 1], &listProcess[j]);
                sorted = false;
            }
        }

        if (sorted == true)
            return;
    }
}


void sortById(Process * listProcess, int n)
{
    int i = 0;
    int j = 0;
    bool sorted;
    for(i=0; i<n-1; i++)
    {
        sorted = true;
        for(j=0; j<n-1; j++)
        {
            if(listProcess[i].state == FINISHED)
                continue;

            else if(listProcess[j + 1].id < listProcess[j].id)           
            {
                swapProcess(&listProcess[j+1], &listProcess[j]);
                sorted = false;
            }
        }   

        if(sorted == true)
            return;
    }
}

float * getAllWaitingTimes(Process * listProcess, int n)
{
    float * arrayWaitingTime = (float *) calloc(n, sizeof(float));
    for(int i=0;i<n;i++)
        arrayWaitingTime[i] = listProcess[i].waitingTime;
    return arrayWaitingTime;
}

float * getAllTurnaroundTimes(Process * listProcess, int n)
{
    float * arrayTurnaroundTime = (float *) calloc (n, sizeof(float));
    for(int i=0;i<n;i++)
        arrayTurnaroundTime[i] = listProcess[i].turnaroundTime;
    return arrayTurnaroundTime;
}