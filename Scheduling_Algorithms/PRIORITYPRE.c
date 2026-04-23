#include "../Algorithms.h"
#include "../utils.h"
#include <limits.h>

void priority_p(Process p[], int n) {

  int remaining[n];
  int started[n];

  for (int i = 0; i < n; i++) {
    remaining[i] = p[i].execution_timet;
    started[i] = 0;
  }

  int time = 0;
  int completed = 0;

  while (completed < n) {

    int idx = -1;
    int best_pri = INT_MAX;

    for (int i = 0; i < n; i++) {
      // pike the one that is still have remining and his time has arrived
      if (remaining[i] > 0 && p[i].arrival_time <= time) {
        // pick the moset priority
        if (p[i].priorty < best_pri) {
          best_pri = p[i].priorty;
          idx = i;
        }
        // if same prioritythe pick earlier arrival
        else if (p[i].priorty == best_pri &&
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

    // idx = -1 then there is no process in the crr has arrival jump to next
    // arrival
    if (idx == -1) {
      int next = INT_MAX;
      for (int i = 0; i < n; i++)
        if (remaining[i] > 0 && p[i].arrival_time < next)
          next = p[i].arrival_time;
      if (next != INT_MAX)
        time = next;
      continue;
    }

    // record response time on first time this process gets CPU
    if (!started[idx]) {
      p[idx].respanse_time = time - p[idx].arrival_time;
      started[idx] = 1;
    }

    // run 1 tick then re-evaluate (this is what makes it preemptive)
    remaining[idx]--;
    time++;

    // process finished
    if (remaining[idx] == 0) {
      p[idx].completion_timet = time;
      p[idx].turnaroundtime = p[idx].completion_timet - p[idx].arrival_time;
      p[idx].waiting_timet = p[idx].turnaroundtime - p[idx].execution_timet;
      completed++;
    }
  }

  print_results(p, n, "Priority (Preemptive)");
}
