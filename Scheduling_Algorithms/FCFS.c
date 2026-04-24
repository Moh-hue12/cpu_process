#include "../Algorithms.h"
#include "../utils.h"
//-------------------------------------------------------------------------------------
// the fcfs with sorting algorithme
//// we sort the procces from the 1st arrived to the last one
/// but on real life we don't know when the procces will arive sow it
/// want work then
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// void insertionSort_by_at(Process arr[], int n) {
//   for (int i = 1; i < n; ++i) {
//     Process key = arr[i];
//     int j = i - 1;
//
//     while (j >= 0 && arr[j].at > key.at) {
//       arr[j + 1] = arr[j];
//       j = j - 1;
//     }
//     arr[j + 1] = key;
//   }
// }
//
// void fcfs(Process p[], int n) {
//   printf("\n=== FCFS Scheduling ===\n");
//   insertionSort_by_at(p, n);
//
//   int time = 0;
//
//   for (int i = 0; i < n; i++) {
//     if (time < p[i].at)
//       time = p[i].at; // handle if the procce 1 ended and the Process 2
//       didn't
//                       // arrive yet
//
//     p[i].rt = time - p[i].at;
//     time += p[i].et;
//     p[i].ct = time;
//     p[i].tat = p[i].ct - p[i].at;
//     p[i].wt = p[i].tat - p[i].et;
//   }
//
//   // Gantt Chart
//   printf("\nGantt Chart:\n|");
//   for (int i = 0; i < n; i++)
//     printf(" P%d |", p[i].id);
//
//   // recompute start times for gantt display
//   printf("\n");
//   time = 0;
//   for (int i = 0; i < n; i++) {
//     if (time < p[i].at)
//       time = p[i].at;
//     printf("%-4d  ", time);
//     time += p[i].et;
//   }
//   printf("%-4d", time);
//
//   // Table
//   printf("\n\nP   | AT | ET | CT | TAT | WT | RT\n");
//   printf("------------------------------------\n");
//   float avg_tat = 0, avg_wt = 0, avg_rt = 0;
//   for (int i = 0; i < n; i++) {
//     printf("P%-2d | %-2d | %-2d | %-2d | %-3d | %-2d | %-2d\n", p[i].id,
//            p[i].at, p[i].et, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
//     printf("------------------------------------\n");
//     avg_tat += p[i].tat;
//     avg_wt += p[i].wt;
//     avg_rt += p[i].rt;
//   }
//   printf("Avg TAT = %.2f\n", avg_tat / n);
//   printf("Avg WT  = %.2f\n", avg_wt / n);
//   printf("Avg RT  = %.2f\n", avg_rt / n);
// }
//

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// the fcfs with queue
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

void fcfs(Process p[], int n) {
  Queue *queue = create_queue();
  int j = 0;
  int time = 0; // current time
  int in_queue[n];
  for (int j = 0; j < n; j++)
    in_queue[j] = 0;

  // we make a loop that loop all process then on each iteration we add
  // the arrived process on the current time to the queue an mark it
  // sow we don't add it again one
  // the next iteration, then we pop from Queue the 1st process
  // and calc the informaation and print them
  // then the current time increased to the time where the current procces ended
  // sow the next one start , and start the iteration all over again

  /* Gantt */
  int gantt_pid[n + 1];
  int gantt_start[n + 2];
  int gantt_len = 0;

  while (j < n) {

    // we add the arrived process to the queue
    // sow we loop them all ,and if the p[i].at = time or less then it
    // then the procss time has arrived and we make sure we don't add the same
    // process we added on prevouse iteration
    for (int i = 0; i < n; i++) {
      if (p[i].arrival_time <= time && !in_queue[i]) {
        enqueue(queue, &p[i]);
        in_queue[i] = 1;
      }
    }

    // if the current process a end and next one b didn't arrive yet
    // we now that by see if there is a process added to the queue
    // if is it empty then the p[i].at(the arrive t of b) > time
    // (time in this moment refer to the execution time to the all procees
    // beffor b), sow we move time to the time that b arrived
    if (is_empty(queue)) {
      // find the earliest arrival time among processes not yet added to the
      // queue
      int next_arrival = -1;
      for (int i = 0; i < n; i++) {
        if (!in_queue[i]) {
          if (next_arrival == -1 || p[i].arrival_time < next_arrival) {
            next_arrival = p[i].arrival_time;
          }
        }
      }
      if (next_arrival != -1) {
        /* record idle slot */
        gantt_pid[gantt_len] = -1;
        gantt_start[gantt_len] = time;
        gantt_len++;
        time = next_arrival;
      }
      continue;
    }

    Process *current = dequeue(queue);

    /* record bar */
    gantt_pid[gantt_len] = current->id;
    gantt_start[gantt_len] = time;
    gantt_len++;

    current->respanse_time = time - current->arrival_time;
    // time become the total exection time from the start to the current process
    time += current->execution_timet;
    current->completion_timet = time;
    current->turnaroundtime = current->completion_timet - current->arrival_time;
    current->waiting_timet = current->turnaroundtime - current->execution_timet;

    j++;
  }

  /* close last bar */
  gantt_start[gantt_len] = time;
  print_gantt(gantt_pid, gantt_start, gantt_len);
  free(queue);
  print_results(p, n, "FCFS");
}
