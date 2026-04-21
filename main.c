#include "Scheduling_Algorithms/Algorithms.h"

#define MAX_Size 100

int main() {
  // char buffer[MAX_Size];
  // int np, quantum, num_queues;
  //
  // // 1. Number of processes
  // printf("Enter number of processes: ");
  // fgets(buffer, sizeof(buffer), stdin);
  // sscanf(buffer, "%d", &np);
  //
  // // Allocate array of Process
  // Process *p = malloc(np * sizeof(Process));
  //
  // // 2. Read each process: id, at, bt, priority
  // for (int i = 0; i < np; i++) {
  //   printf("\n--- Process %d ---\n", i + 1);
  //   printf("  Identifier: ");
  //   fgets(buffer, sizeof(buffer), stdin);
  //   sscanf(buffer, "%d", &p[i].id);
  //   printf("  Arrival time: ");
  //   fgets(buffer, sizeof(buffer), stdin);
  //   sscanf(buffer, "%d", &p[i].at);
  //   printf("  Burst time: ");
  //   fgets(buffer, sizeof(buffer), stdin);
  //   sscanf(buffer, "%d", &p[i].et);
  //   printf("  Priority: ");
  //   fgets(buffer, sizeof(buffer), stdin);
  //   sscanf(buffer, "%d", &p[i].pr);

  // // Initialize remaining fields to 0 (will be computed later)
  // p[i].ct = p[i].tat = p[i].wt = p[i].rt = 0;
  //}

  // // 3. Quantum for Round Robin
  // printf("\nEnter time quantum for Round Robin: ");
  // fgets(buffer, sizeof(buffer), stdin);
  // sscanf(buffer, "%d", &quantum);

  // // 4. Multilevel Queue: number of queues and their priorities
  // printf("Enter number of queues for Multilevel Queue Scheduling: ");
  // fgets(buffer, sizeof(buffer), stdin);
  // sscanf(buffer, "%d", &num_queues);
  // int *queue_priorities = malloc(num_queues * sizeof(int));
  // for (int i = 0; i < num_queues; i++) {
  //   printf("  Priority of queue %d: ", i + 1);
  //   fgets(buffer, sizeof(buffer), stdin);
  //   sscanf(buffer, "%d", &queue_priorities[i]);
  // }
  int np = 4;
  Process p[4];

  // Process 1
  p[0].id = 1;
  p[0].at = 0;
  p[0].et = 5;

  // Process 2
  p[1].id = 2;
  p[1].at = 1;
  p[1].et = 3;

  // Process 3
  p[2].id = 3;
  p[2].at = 2;
  p[2].et = 8;

  // Process 4
  p[3].id = 4;
  p[3].at = 4;
  p[3].et = 2;
  // Optional: print what was read (to verify)
  printf("\n=== Input Summary ===\n");
  for (int i = 0; i < np; i++) {
    printf("Process %d: id=%d, at=%d, bt=%d, prio=%d\n", i + 1, p[i].id,
           p[i].at, p[i].et, p[i].pr);
  }
  // printf("Round Robin quantum = %d\n", quantum);
  // printf("Multilevel queues priorities: ");
  // for (int i = 0; i < num_queues; i++)
  //   printf("%d ", queue_priorities[i]);
  // printf("\n");

  sjf(p, np);

  // Free allocated memory
  // free(p);
  // free(priority);
  // free(queue_priorities);

  return 0;
}
