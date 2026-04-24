/*
 * srtf.c  –  Shortest Remaining Time First (preemptive SJF)
 *
 * At every clock tick we check all arrived processes and hand the CPU
 * to the one with the shortest *remaining* burst.  If a new process
 * arrives with a shorter remaining time than the running one, it
 * immediately preempts the current process.
 *
 * Tie-breaking: if two processes have the same remaining time,
 * the one that arrived earlier wins.
 *
 * Time complexity: O(n * total_burst)  – suitable for a simulator.
 */

#include "../Algorithms.h"
#include "../utils.h"

void srtf(Process p[], int n) {
  /* ── Local working copy ── */
  /* remaining[i] tracks how many burst units process i still needs;
     initialised from execution_timet and decremented each tick */
  int remaining[n];
  /* response[i] holds the response time of process i;
     -1 means "not started yet" */
  int response[n];

  for (int i = 0; i < n; i++) {
    remaining[i] = p[i].execution_timet; /* initialise remaining burst */
    response[i] = -1;                    /* -1 means "not started yet" */
    p[i].completion_timet = p[i].turnaroundtime = p[i].waiting_timet = 0;
  }

  /* Gantt chart stored as (process_id, start_time) runs.
     We compress consecutive identical entries into one bar. */
  int gantt_pid[2000];
  int gantt_start[2001];
  int gantt_len = 0;

  int current_time = 0;
  int completed = 0;

  /* Find the time at which the last process arrives (upper bound for loop) */
  int total_time = 0;
  for (int i = 0; i < n; i++)
    total_time += p[i].execution_timet;
  /* Add the maximum arrival time in case there are gaps */
  int max_arrival = 0;
  for (int i = 0; i < n; i++)
    if (p[i].arrival_time > max_arrival)
      max_arrival = p[i].arrival_time;
  total_time += max_arrival; /* safe upper bound */

  int prev_pid =
      -1; /* track process running in previous tick for Gantt compression */

  while (completed < n) {
    /* ── Pick the process with shortest remaining time among arrived ones ── */
    int idx = -1;
    for (int i = 0; i < n; i++) {
      if (remaining[i] > 0 && p[i].arrival_time <= current_time) {
        if (idx == -1 || remaining[i] < remaining[idx] ||
            (remaining[i] == remaining[idx] &&
             p[i].arrival_time < p[idx].arrival_time))
          idx = i;
      }
    }

    if (idx == -1) {
      /* CPU idle: jump to the next arrival */
      int next = total_time;
      for (int i = 0; i < n; i++)
        if (remaining[i] > 0 && p[i].arrival_time < next)
          next = p[i].arrival_time;

      /* Record idle slot in Gantt */
      if (prev_pid != -1) {
        gantt_pid[gantt_len] = -1; /* -1 = idle */
        gantt_start[gantt_len] = current_time;
        gantt_start[gantt_len + 1] = next;
        gantt_len++;
      }
      current_time = next;
      prev_pid = -1;
      continue;
    }

    /* ── Record response time on first CPU access ── */
    if (response[idx] == -1)
      response[idx] = current_time - p[idx].arrival_time;

    /* ── Gantt chart: start a new bar if the running process changed ── */
    if (p[idx].id != prev_pid) {
      gantt_pid[gantt_len] = p[idx].id;
      gantt_start[gantt_len] = current_time;
      gantt_len++;
      prev_pid = p[idx].id;
    }

    /* ── Execute for one time unit ── */
    remaining[idx]--;
    current_time++;

    /* ── Check if process finished ── */
    if (remaining[idx] == 0) {
      p[idx].completion_timet = current_time;
      p[idx].turnaroundtime = current_time - p[idx].arrival_time;
      p[idx].waiting_timet = p[idx].turnaroundtime - p[idx].execution_timet;
      p[idx].respanse_time = response[idx];
      completed++;
    }
  }

  /* Close the last Gantt bar */
  gantt_start[gantt_len] = current_time;
  print_gantt(gantt_pid, gantt_start, gantt_len);

  /* ── Copy computed stats back to caller's array (matched by id) ── */
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (p[i].id == p[j].id) {
        p[i].completion_timet = p[j].completion_timet;
        p[i].turnaroundtime = p[j].turnaroundtime;
        p[i].waiting_timet = p[j].waiting_timet;
        p[i].respanse_time = p[j].respanse_time;
      }

  print_results(p, n, "SRTF (Preemptive SJF)");
}
