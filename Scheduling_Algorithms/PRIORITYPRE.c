#include "../Algorithms.h"
#include "../utils.h"
#include <limits.h>
/*
 * we make a loop that loop all process then each time we loop all process to
 * find the heighst prioriyt procees and still have reminng if two have the same
 * pr we take the 1st arrived if even this
 * (that is impossible to two process to arriv at the same time)
 * we pick by id
 * then  if the cpu is idl we jump to the time the next process arrived
 * then we decrase the remining exuction time for the choisen process
 * by the time nedded to the next process to arrive
 * (this don't mean we will stop the process the next time a process arrived ,
 * no we just stop it to see is the next process have a priority more then him
 * if no he will be processed again )
 * then if there is no remianing we start calculation
 */
void priority_p(Process p[], int n) {
  // remaining array to track the remaining time for  process i
  // i in the remaining array is the same process i on the process array
  int remaining[n];
  int started[n];
  for (int i = 0; i < n; i++) {
    remaining[i] = p[i].execution_timet;
    started[i] = 0;
  }

  /* Gantt chart stored as (process_id, start_time) runs.
     We compress consecutive identical entries into one bar. */
  int gantt_pid[2000];
  int gantt_start[2001];
  int gantt_len = 0;
  int prev_pid = -1;

  int time = 0;
  int completed = 0;
  while (completed < n) {
    int idx = -1;
    int best_pri = INT_MAX;
    for (int i = 0; i < n; i++) {
      // pike the one that is still have remining and his time has arrived
      if (remaining[i] > 0 && p[i].arrival_time <= time) {
        // pick the heighest priority
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
      if (next != INT_MAX) {
        /* record idle slot in Gantt */
        if (prev_pid != -1) {
          gantt_pid[gantt_len] = -1;
          gantt_start[gantt_len] = time;
          gantt_len++;
        }
        prev_pid = -1;
        time = next;
      }
      continue;
    }
    // record response time on first time this process gets CPU
    if (!started[idx]) {
      p[idx].respanse_time = time - p[idx].arrival_time;
      started[idx] = 1;
    }
    // Gantt chart: start a new bar if the running process changed
    if (p[idx].id != prev_pid) {
      gantt_pid[gantt_len] = p[idx].id;
      gantt_start[gantt_len] = time;
      gantt_len++;
      prev_pid = p[idx].id;
    }
    // we try to increase time to the time the next process arrived
    // to avoid iincrease one by one(just optimiztion)
    // sow on start we assume that the process run to finish
    // then loop all the process we have and find colssest processt to arrive
    // we use gap for that (gap is how much the next process need to arrive)
    // and comapre  it with silce for sow slice on the end get the smallest gap
    int slice = remaining[idx]; /* assume it runs to completion */
    for (int i = 0; i < n; i++) {
      if (remaining[i] > 0 && p[i].arrival_time > time) {
        int gap = p[i].arrival_time - time;
        if (gap < slice)
          slice = gap; /* a process arrives sooner, cap the slice */
      }
    }
    /* jump the whole slice at once instead of ticking one by one */
    remaining[idx] -= slice;
    time += slice;
    // process finished
    if (remaining[idx] == 0) {
      p[idx].completion_timet = time;
      p[idx].turnaroundtime = p[idx].completion_timet - p[idx].arrival_time;
      p[idx].waiting_timet = p[idx].turnaroundtime - p[idx].execution_timet;
      completed++;
    }
  }
  /* close last bar */
  gantt_start[gantt_len] = time;
  print_gantt(gantt_pid, gantt_start, gantt_len);
  print_results(p, n, "Priority (Preemptive)");
}
