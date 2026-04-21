#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
  int id;
  int at; // Arrival Time
  int et; // Execution Time (Burst Time)
  int pr;
  int ct;  // Completion Time
  int tat; // Turnaround Time
  int wt;  // Waiting Time
  int rt;  // Response Time

} Process;

void fcfs(Process p[], int n);
void sjf(Process p[], int n);
