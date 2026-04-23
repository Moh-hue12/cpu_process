#include "../Algorithms.h"
#include "../utils.h"
#include <limits.h>

void priority_np(Process p[], int n) {

  int done[n];
  for (int i = 0; i < n; i++)
    done[i] = 0;

  int time = 0;
  int completed = 0;

  while (completed < n) {

    int idx = -1;
    int best_pri = INT_MAX;

    for (int i = 0; i < n; i++) {
      // we try to get all process that has arrived on the current time but they
      // don't done yet
      //
      if (!done[i] && p[i].arrival_time <= time) {
        // we search for the process with heighest priorty
        if (p[i].priorty < best_pri) {
          best_pri = p[i].priorty;
          idx = i;
          // if two process have the same priority we we take the 1st one
        } else if (p[i].priorty == best_pri &&
                   p[i].arrival_time < p[idx].arrival_time) {
          idx = i;
          // if they have the same priority and arrival time we just pick by id
          // because its i impposible to two process to have exactly tht e same
          // arrival time
        } else if (p[i].priorty == best_pri &&
                   p[i].arrival_time == p[idx].arrival_time &&
                   p[i].id < p[idx].id) {
          idx = i;
        }
      }
    }

    // if all process completed and no one arrivaed yet we jump to the time thar
    // the next procces arrivd on it
    if (idx == -1) {
      int next = INT_MAX;
      for (int i = 0; i < n; i++)
        if (!done[i] && p[i].arrival_time < next)
          next = p[i].arrival_time;
      if (next != INT_MAX)
        time = next;
      continue;
    }

    p[idx].respanse_time = time - p[idx].arrival_time;
    time += p[idx].execution_timet;
    p[idx].completion_timet = time;
    p[idx].turnaroundtime = p[idx].completion_timet - p[idx].arrival_time;
    p[idx].waiting_timet = p[idx].turnaroundtime - p[idx].execution_timet;

    done[idx] = 1;
    completed++;
  }

  print_results(p, n, "Priority (Non-Preemptive)");
}

// int main() {
//   int np, quantum, num_queues, choice;
//   Process *p = NULL;
//
//   printf("Enter number of processes: ");
//   scanf("%d", &np);
//   p = (Process *)malloc(np * sizeof(Process));
//   if (!p) {
//     printf("Memory allocation failed\n");
//     return 1;
//   }
//
//   for (int i = 0; i < np; i++) {
//     printf("\n--- Process %d ---\n", i + 1);
//     printf("  Identifier: ");
//     scanf("%d", &p[i].id);
//     printf("  Arrival time: ");
//     scanf("%d", &p[i].arrival_time);
//     printf("  Burst time: ");
//     scanf("%d", &p[i].execution_timet);
//     printf("  Priority: ");
//     scanf("%d", &p[i].priorty);
//     p[i].completion_timet = p[i].turnaroundtime = p[i].waiting_timet =
//         p[i].respanse_time = 0;
//     p[i].pid = -1;
//   }
//
//   priority_p(p, np);
// }
