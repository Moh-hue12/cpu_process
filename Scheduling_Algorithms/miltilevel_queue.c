#include "../Algorithms.h"
#include "../utils.h"
#include <limits.h>

void insertionSort_by_pr(QueueLevel arr[], int n) {
  for (int i = 1; i < n; ++i) {
    QueueLevel key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j].priority > key.priority) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

void multilevel_queue(QueueLevel queues[], int num_queues,
                      Process *all_processes[], int total_processes) {
  //  Sort queues by priority
  insertionSort_by_pr(queues, num_queues);

  // See if a process added to his queue or not
  int *added = calloc(total_processes, sizeof(int));
  int time = 0;
  int completed = 0;

  while (completed < total_processes) {
    // Add all processes that have arrived by current time to their
    // respective queues
    for (int i = 0; i < total_processes; i++) {
      Process *p = all_processes[i];
      if (!added[i] && p->arrival_time <= time) {
        int pid = p->pid;
        if (queues[pid].algo == ALGO_FCFS) {
          enqueue(queues[pid].fcfs_queue, p);
        } else if (queues[pid].algo == ALGO_SJF) {
          heap_push(queues[pid].sjf_heap, p);
        }
        added[i] = 1;
      }
    }

    // Find the heighst priority queue
    // and not being empty
    int selected_q = -1;
    for (int q = 0; q < num_queues; q++) {
      int non_empty = 0;
      if (queues[q].algo == ALGO_FCFS && !is_empty(queues[q].fcfs_queue))
        non_empty = 1;
      else if (queues[q].algo == ALGO_SJF && !heap_is_empty(queues[q].sjf_heap))
        non_empty = 1;
      if (non_empty) {
        selected_q = q;
        break;
      }
    }

    //  If no process ready, jump time to next arrival
    // it select the smallest exucution time and jump
    // better then incrment time by one , qhich will take time
    if (selected_q == -1) {
      int next_arrival = INT_MAX;
      for (int i = 0; i < total_processes; i++) {
        if (!added[i] && all_processes[i]->arrival_time < next_arrival)
          next_arrival = all_processes[i]->arrival_time;
      }
      if (next_arrival != INT_MAX) {
        time = next_arrival;
        continue;
      } else {
        break; // should not happen
      }
    }

    //  Get the process from the selected queue according to its
    // algorithm
    Process *current = NULL;
    if (queues[selected_q].algo == ALGO_FCFS) {
      current = dequeue(queues[selected_q].fcfs_queue);
    } else if (queues[selected_q].algo == ALGO_SJF) {
      current = heap_pop(queues[selected_q].sjf_heap);
    }

    current->respanse_time = time - current->arrival_time;
    time += current->execution_timet;
    current->completion_timet = time;
    current->turnaroundtime = current->completion_timet - current->arrival_time;
    current->waiting_timet = current->turnaroundtime - current->execution_timet;

    completed++;
  }

  //  Print results
  printf("\n===== Multilevel Queue Scheduling =====\n");
  printf("Number of queues: %d\n", num_queues);
  for (int q = 0; q < num_queues; q++) {
    printf("Queue %d: priority = %d, algorithm = %s\n", q, queues[q].priority,
           (queues[q].algo == ALGO_FCFS) ? "FCFS" : "SJF");
  }
  printf("\nP   | AT | BT | CT | TAT | WT | RT | Queue\n");
  printf("--------------------------------------------\n");
  float sum_tat = 0, sum_wt = 0, sum_rt = 0;
  for (int i = 0; i < total_processes; i++) {
    Process *p = all_processes[i];
    printf("P%-2d | %-2d | %-2d | %-2d | %-3d | %-2d | %-2d |  Q%d\n", p->id,
           p->arrival_time, p->execution_timet, p->completion_timet,
           p->turnaroundtime, p->waiting_timet, p->respanse_time, p->pid);
    printf("--------------------------------------------\n");
    sum_tat += p->turnaroundtime;
    sum_wt += p->waiting_timet;
    sum_rt += p->respanse_time;
  }
  printf("Average Turnaround Time = %.2f\n", sum_tat / total_processes);
  printf("Average Waiting Time    = %.2f\n", sum_wt / total_processes);
  printf("Average Response Time   = %.2f\n", sum_rt / total_processes);

  free(added);
}
