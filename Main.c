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
    Process* ganttProcessList = NULL;
    int lenGanttProcessList;
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

    ganttProcessList = listProcess;
    lenGanttProcessList = n;
    switch (option)
    {
        case 1:
            fcfs(listProcess, n);
            break;
        case 2:
            sjf(listProcess, n);
            break;
        case 3:
            ganttProcessList = srtf(listProcess, n, &lenGanttProcessList);
            break;
        case 4:
            printf("Is Priority Reversed? [Enter 1/0]: ");
            scanf("%d", &temp);
            priorityReversed = temp;
            priorityNonPreemptive(listProcess, n, priorityReversed);
            break;
        case 5:
            printf("Is Priority Reversed? [Enter 1/0]: ");
            scanf("%d", &temp);
            priorityReversed = temp;
            ganttProcessList = priorityPreemptive(listProcess, n, priorityReversed, &lenGanttProcessList);
            break;
        case 6:
            //roundRobin();
            break;
        default:
            break;
    }

    displayGantt(ganttProcessList, lenGanttProcessList);
    displayProcesses(listProcess, n);
    printf("\nAverage Turnaround Time => %.2f\n", averageTurnaroundTime(listProcess, n));
    printf("Average Waiting Time => %.2f\n\n", averageWaitingTime(listProcess, n));

    if(ganttProcessList != listProcess)
        free(ganttProcessList);
    
    free(listProcess);
    listProcess = NULL;
    ganttProcessList = NULL;

    return 0;
}