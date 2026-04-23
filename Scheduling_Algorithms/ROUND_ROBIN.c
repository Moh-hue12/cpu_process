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

  // Sort by completion time (almost like gantt)
  for (int i = 0; i < proc_count - 1; i++) {
    for (int j = i + 1; j < proc_count; j++) {
      if (result[i].completion_timet > result[j].completion_timet) {
        Process temp = result[i];
        result[i] = result[j];
        result[j] = temp;
      }
    }
  }

  print_results(result, proc_count, "Round Robin");
  free(remaining);
  free(started);
  free(result);
  free_queue(queue);
}
