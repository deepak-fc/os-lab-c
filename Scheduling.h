#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Process.h"
#include "Utilities.h"

typedef enum
{
	FCFS,
	SJF,
	SRTF,
	PRIORITY_NON_PREEMPTIVE,
	PRIORITY_PREEMPTIVE,
	ROUND_ROBIN

}AlgoName;

void nonPreemptiveScheduler(Process* listProcess, int n, AlgoName algoName, bool reverseSort);
Process* preemptiveScheduler(Process* listProcess, int n, AlgoName algoName, bool reverseSort, int* newLength);

void executeProcess(Process* p, float currentTime, int maxTimePeriod);
void displayGantt(Process * listProcess, int n);
float averageWaitingTime(Process * listProcess, int n);
float averageTurnaroundTime(Process * listProcess, int n);