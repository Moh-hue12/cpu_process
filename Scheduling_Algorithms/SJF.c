#include "../utils.h"
#define MAX_CAP 1000
#include <limits.h>

#include "../Algorithms.h"
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

void sjf(Process p[], int n) {

  MinHeap *heap = create_heap(MAX_CAP);
  int in_heap[n];
  for (int i = 0; i < n; i++)
    in_heap[i] = 0;

  int time = 0;
  int completed = 0;

  while (completed < n) {

    // push all arrived processes not yet in heap
    // the heap is min-heap sow the one with lowest execution time is placed on the start
    // and offcurse the other are ordred
    for (int i = 0; i < n; i++) {
      if (!in_heap[i] && p[i].arrival_time <= time) {
        heap_push(heap, &p[i]);
        in_heap[i] = 1;
      }
    }
     

    //same logic on fcfs and all other algorithms if the quur is empty then the cou is idle
    if (heap_is_empty(heap)) {
      int next = INT_MAX;
      for (int i = 0; i < n; i++)
        if (!in_heap[i] && p[i].arrival_time < next)
          next = p[i].arrival_time;
      if (next != INT_MAX)
        time = next;
      continue;
    }

    //we pop the process with the most execution t from the heap and process it 
    Process *current = heap_pop(heap);

    current->respanse_time = time - current->arrival_time;
    time += current->execution_timet;
    current->completion_timet = time;
    current->turnaroundtime = current->completion_timet - current->arrival_time;
    current->waiting_timet = current->turnaroundtime - current->execution_timet;

    completed++;
  }

  free_heap(heap);
  print_results(p, n, "SJF (Non-Preemptive)");
}
