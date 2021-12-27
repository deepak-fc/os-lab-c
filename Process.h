#pragma once
#include "Graphics.h"

typedef enum
{
    EMPTY,
    IDLE,
    FINISHED
    
}ProcessState;

typedef struct Process
{
    int id;
    int priority;
    int initialBurst;
    int burst;
    int remainingBurst;
    float arrivalTime;
    float turnaroundTime;
    float waitingTime;
    float initialStartingTime;
    float startingTime;
    float completionTime;
    float responseTime;

    ProcessState state;

}Process;

void processInit(Process * p);
void updateValues(Process * p);
void displayProcess(Process * p);
void displayProcesses(Process listProcess[], int len);
void processGetUserInput(Process * p);
void swapProcess(Process * a, Process * b);

void sortByArrivalTime(Process * listProcess, int n);
void sortByBurstTime(Process * listProcess, int n);
void sortByPriority(Process* listProcess, int n, bool priorityReverse);
void sortById(Process * listProcess, int n);
float * getAllWaitingTimes(Process * listProcess, int n);
float * getAllTurnaroundTimes(Process * listProcess, int n);