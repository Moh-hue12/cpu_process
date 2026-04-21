#include "../utils.h"
#define MAX_CAP 1000

void srtf(Process p[], int n) {
  MinHeap *heap = create_heap(MAX_CAP);
  int j = 0;
  int time = 0; // current time

  int indx = 0;
  while (j < n) {
    while (indx < n && p[indx].at <= time) {
      heap_push(heap, &p[indx]);
      indx++;
    }

    if (heap_is_empty(heap)) {
      if (indx < n) {
        time = p[indx].at;
      }
      continue;
    }
    Process *current = heap_pop(heap);
    current->rt = time - current->at;
    time += current->et;
    current->ct = time;
    current->tat = current->ct - current->at;
    current->wt = current->tat - current->et;
    j++;
  }

  free_heap(heap);
  print_results(p, n, "SJF (Non-preemptive)");
}
