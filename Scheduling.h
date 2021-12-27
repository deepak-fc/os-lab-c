#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Process.h"
#include "Utilities.h"

void fcfs(Process * listProcess, int n);
void sjf(Process * listProcess, int n);
Process* srtf(Process* listProcess, int n, int* newLength);
void priorityNonPreemptive(Process* listProcess, int n, bool priorityReversed);
Process* priorityPreemptive(Process* listProcess, int n, bool priorityReversed, int* newLength);

void executeProcess(Process* p, float currentTime, int maxTimePeriod);
void displayGantt(Process * listProcess, int n);
float averageWaitingTime(Process * listProcess, int n);
float averageTurnaroundTime(Process * listProcess, int n);