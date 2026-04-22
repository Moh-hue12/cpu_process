#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"
#include "utils.h" // for Queue, MinHeap definitions

typedef enum { ALGO_FCFS, ALGO_SJF, ALGO_RR } AlgoType;

typedef struct QueueLevel {
  int priority;
  AlgoType algo;
  int quantum;
  int size;
  Queue *fcfs_queue;
  MinHeap *sjf_heap;
} QueueLevel;

typedef struct {
  int num_levels;
  QueueLevel *levels;
} MultiLevelQueue;

void fcfs(Process p[], int n);
void sjf(Process p[], int n);
void multilevel_queue(QueueLevel queues[], int num_queues,
                      Process *all_processes[], int total_processes);

#endif
