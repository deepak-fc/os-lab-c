#pragma once
#include "Graphics.h"

typedef enum
{
    EMPTY,
    IDLE,
    FINISHED
    
}ProcessState;

typedef enum
{
    ID,
    BURST,
    ARRIVAL,
    PRIORITY

}SortAttribute;

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
void displayProcess(Process * p);
void displayProcesses(Process listProcess[], int len);
void processGetUserInput(Process * p);
void swapProcess(Process * a, Process * b);
void updateValues(Process* p);

void sortProcessListBy(Process* listProcess, int n, SortAttribute attribute, bool reverse);

float * getAllWaitingTimes(Process * listProcess, int n);
float * getAllTurnaroundTimes(Process * listProcess, int n);