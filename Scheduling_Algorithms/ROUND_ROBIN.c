#include "../utils.h"
#include <assert.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void round_robin(const Process proc_list[], int proc_count, int quantum) {
  Process *result = malloc(sizeof(Process) * proc_count);
  int *remaining = malloc(sizeof(int) * proc_count);
  int *started = calloc(proc_count, sizeof(int)); // flag response time
  assert(result != NULL && remaining != NULL && started != NULL);
  for (int i = 0; i < proc_count; i++) {
    result[i] = proc_list[i];
  }
  // init remaining time
  for (int i = 0; i < proc_count; i++) {
    remaining[i] = proc_list[i].execution_timet;
  }

  /* Gantt chart stored as (process_id, start_time) runs */
  int gantt_pid[2000];
  int gantt_start[2001];
  int gantt_len = 0;

  Queue *queue = create_queue();
  int input_idx = 0;
  int finished_count = 0;
  int current_time = 0;
  while (input_idx < proc_count &&
         result[input_idx].arrival_time <= current_time) {
    enqueue(queue, &result[input_idx]);
    input_idx++;
  }
  while (finished_count < proc_count) {
    if (is_empty(queue)) {
      // skip CPU idle time
      /* record idle slot */
      gantt_pid[gantt_len] = -1;
      gantt_start[gantt_len] = current_time;
      gantt_len++;
      current_time = result[input_idx].arrival_time;
      while (input_idx < proc_count &&
             result[input_idx].arrival_time <= current_time) {
        enqueue(queue, &result[input_idx]);
        input_idx++;
      }
      continue;
    }
    // run the current proc and mark it as started
    Process *current = dequeue(queue);
    int idx = current - result; // pointer arithmetic to find it's index
    if (!started[idx]) {
      current->respanse_time = current_time - current->arrival_time;
      started[idx] = 1;
    }

    /* record bar */
    gantt_pid[gantt_len] = current->id;
    gantt_start[gantt_len] = current_time;
    gantt_len++;

    int run_time = MIN(remaining[idx], quantum);
    remaining[idx] -= run_time;
    current_time += run_time;
    while (input_idx < proc_count &&
           result[input_idx].arrival_time <= current_time) {
      enqueue(queue, &result[input_idx]);
      input_idx++;
    }
    if (remaining[idx] > 0) {
      enqueue(queue, current);
    } else {
      //  finished executing
      current->completion_timet = current_time;
      current->turnaroundtime =
          current->completion_timet - current->arrival_time;
      current->waiting_timet =
          current->turnaroundtime - current->execution_timet;
      finished_count++;
    }
  }

  /* close last bar */
  gantt_start[gantt_len] = current_time;
  print_gantt(gantt_pid, gantt_start, gantt_len);
  print_results(result, proc_count, "Round Robin");
  free(remaining);
  free(started);
  free(result);
  free_queue(queue);
}
