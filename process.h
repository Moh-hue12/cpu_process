#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process {
  int id;
  int arrival_time;    // Arrival Time
  int execution_timet; // Execution Time (Burst Time)
  int priorty;
  int completion_timet; // Completion Time
  int turnaroundtime;   // Turnaround Time
  int waiting_timet;    // Waiting Time
  int respanse_time;    // Response Time
  int pid;              // queue assignment for multilevel queue
} Process;

#endif
