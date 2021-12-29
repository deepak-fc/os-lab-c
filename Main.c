#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#include "Process.h"
#include "Graphics.h"
#include "Utilities.h"
#include "Scheduling.h"

int main(void)
{
    int n = 0;
    int option = 0;
    
    Process* listProcess = NULL;
    Process* ganttList = NULL;
    int lenGanttList;
    
    int temp = 0;
    bool priorityReversed = false;

    clearScreen();
    drawLine(80);
    printf("ALGO MENU\n");
    drawLine(80);
    printf("1) FCFS\n");
    printf("2) SJF\n");
    printf("3) SRTF\n");
    printf("4) PRIORITY (NON-PREEMPTIVE)\n");
    printf("5) PRIORITY (PREEMPTIVE)\n");
    printf("6) ROUND ROBIN\n\n");

    printf("Enter an option: ");
    scanf("%d", &option);

    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    listProcess = (Process*)calloc(n, sizeof(Process));
    for (int i = 0; i < n; i++)
        processInit(&listProcess[i]);

    drawLine(80);
    for (int i = 0; i < n; i++)
        processGetUserInput(&listProcess[i]);

    ganttList = listProcess;
    lenGanttList = n;
    switch (option)
    {
        case 1:
            nonPreemptiveScheduler(listProcess, n, FCFS, false);
            break;
        case 2:
            nonPreemptiveScheduler(listProcess, n, SJF, false);
            break;
        case 3:
            ganttList = preemptiveScheduler(listProcess, n, SRTF, false, &lenGanttList);
            break;
        case 4:
            printf("Is Priority Reversed? [Enter 1/0]: ");
            scanf("%d", &temp);
            priorityReversed = temp;
            nonPreemptiveScheduler(listProcess, n, PRIORITY_NON_PREEMPTIVE, priorityReversed);
            break;
        case 5:
            printf("Is Priority Reversed? [Enter 1/0]: ");
            scanf("%d", &temp);
            priorityReversed = temp;
            ganttList = preemptiveScheduler(listProcess, n, PRIORITY_PREEMPTIVE, priorityReversed, &lenGanttList);
            break;
        case 6:
            //roundRobin();
            break;
        default:
            break;
    }

    displayGantt(ganttList, lenGanttList);
    displayProcesses(listProcess, n);
    printf("\nAverage Turnaround Time => %.2f\n", averageTurnaroundTime(listProcess, n));
    printf("Average Waiting Time => %.2f\n\n", averageWaitingTime(listProcess, n));

    if(ganttList != listProcess)
        free(ganttList);
    
    free(listProcess);
    listProcess = NULL;
    ganttList = NULL;

    return 0;
}