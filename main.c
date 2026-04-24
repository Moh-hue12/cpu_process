#include "Algorithms.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int np, quantum, num_queues, choice;
  Process *p = NULL;

  printf("Enter number of processes: ");
  scanf("%d", &np);
  p = (Process *)malloc(np * sizeof(Process));
  if (!p) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < np; i++) {
    printf("\n--- Process %d ---\n", i + 1);
    printf("  Identifier: ");
    scanf("%d", &p[i].id);
    printf("  Arrival time: ");
    scanf("%d", &p[i].arrival_time);
    printf("  Burst time: ");
    scanf("%d", &p[i].execution_timet);
    printf("  Priority: ");
    scanf("%d", &p[i].priorty);
    p[i].completion_timet = p[i].turnaroundtime = p[i].waiting_timet =
        p[i].respanse_time = 0;
    p[i].pid = -1;
  }

  insertionSort_by_at(p, np);

  printf("\nEnter time quantum for Round Robin: ");
  scanf("%d", &quantum);

  printf("\n========== Scheduling Algorithms ==========\n");
  printf("1. First Come First Served (FCFS)\n");
  printf("2. Shortest Job First (SJF) – non-preemptive\n");
  printf("3. Multilevel Queue (FCFS/SJF per queue)\n");
  printf("4. Priority – preemptive\n");
  printf("5. Priority – non-preemptive\n");
  printf("6. Round robin\n");
  printf("2. Shortest Remaining Time First (SRTF) – non-preemptive\n");
  printf("Enter your choice: ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    fcfs(p, np);
    break;
  case 2:
    sjf(p, np);
    break;
  case 3: {
    printf("\nEnter number of queues: ");
    scanf("%d", &num_queues);
    QueueLevel *queues = (QueueLevel *)malloc(num_queues * sizeof(QueueLevel));
    if (!queues) {
      free(p);
      return 1;
    }
    for (int i = 0; i < num_queues; i++) {
      printf("\n--- Queue %d ---\n", i);
      printf("  Priority (lower = higher): ");
      scanf("%d", &queues[i].priority);
      printf("  Algorithm (0=FCFS,1=SJF): ");
      int algo_choice;
      scanf("%d", &algo_choice);
      queues[i].algo = (algo_choice == 0) ? ALGO_FCFS : ALGO_SJF;
      queues[i].quantum = 0;
      queues[i].size = 0;
      if (queues[i].algo == ALGO_FCFS) {
        queues[i].fcfs_queue = create_queue();
        queues[i].sjf_heap = NULL;
      } else {
        queues[i].fcfs_queue = NULL;
        queues[i].sjf_heap = create_heap(10);
      }
    }
    printf("\n--- Process to Queue Assignment ---\n");
    for (int i = 0; i < np; i++) {
      printf("Process %d (ID=%d): queue index (0..%d): ", i + 1, p[i].id,
             num_queues - 1);
      int qid;
      scanf("%d", &qid);
      while (qid < 0 || qid >= num_queues) {
        printf("Invalid. Enter 0..%d: ", num_queues - 1);
        scanf("%d", &qid);
      }
      p[i].pid = qid;
    }
    Process **proc_ptrs = (Process **)malloc(np * sizeof(Process *));
    for (int i = 0; i < np; i++)
      proc_ptrs[i] = &p[i];
    multilevel_queue(queues, num_queues, proc_ptrs, np);
    for (int i = 0; i < num_queues; i++) {
      if (queues[i].fcfs_queue)
        free_queue(queues[i].fcfs_queue);
      if (queues[i].sjf_heap)
        free_heap(queues[i].sjf_heap);
    }
    free(queues);
    free(proc_ptrs);
    break;
  }
  case 4:
    priority_p(p, np);
    break;

  case 5:
    priority_np(p, np);
    break;

  case 6:
    round_robin(p, np, quantum);
    break;
  case 7:
    srtf(p, np);
    break;
  default:
    printf("Invalid choice.\n");
  }
  free(p);
  return 0;
}
