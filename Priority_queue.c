#include "utils.h"
#include <stdlib.h>

// Helper: swap two Process pointers
static void swap(Process **a, Process **b) {
  Process *temp = *a;
  *a = *b;
  *b = temp;
}

static void heapify_up(MinHeap *heap, int idx) {
  while (idx > 0) {
    int parent = (idx - 1) / 2;
    if (heap->arr[parent]->execution_timet > heap->arr[idx]->execution_timet ||
        (heap->arr[parent]->execution_timet ==
             heap->arr[idx]->execution_timet &&
         heap->arr[parent]->arrival_time > heap->arr[idx]->arrival_time)) {
      swap(&heap->arr[parent], &heap->arr[idx]);
      idx = parent;
    } else {
      break;
    }
  }
}

static void heapify_down(MinHeap *heap, int idx) {
  int left, right, smallest;
  while (1) {
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    smallest = idx;
    if (left < heap->size &&
        (heap->arr[left]->execution_timet <
             heap->arr[smallest]->execution_timet ||
         (heap->arr[left]->execution_timet ==
              heap->arr[smallest]->execution_timet &&
          heap->arr[left]->arrival_time < heap->arr[smallest]->arrival_time))) {
      smallest = left;
    }
    if (right < heap->size && (heap->arr[right]->execution_timet <
                                   heap->arr[smallest]->execution_timet ||
                               (heap->arr[right]->execution_timet ==
                                    heap->arr[smallest]->execution_timet &&
                                heap->arr[right]->arrival_time <
                                    heap->arr[smallest]->arrival_time))) {
      smallest = right;
    }
    if (smallest != idx) {
      swap(&heap->arr[idx], &heap->arr[smallest]);
      idx = smallest;
    } else {
      break;
    }
  }
}

MinHeap *create_heap(int capacity) {
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  if (!heap) {
    printf("Failed to allocate heap\n");
    return NULL;
  }
  heap->arr = (Process **)malloc(capacity * sizeof(Process *));
  if (!heap->arr) {
    printf("Failed to allocate heap array\n");
    free(heap);
    return NULL;
  }
  heap->size = 0;
  heap->capacity = capacity;
  return heap;
}

void heap_push(MinHeap *heap, Process *p) {
  if (!heap)
    return;
  if (heap->size >= heap->capacity) {
    int new_cap = heap->capacity * 2;
    Process **new_arr =
        (Process **)realloc(heap->arr, new_cap * sizeof(Process *));
    if (!new_arr) {
      printf("Heap reallocation failed\n");
      return;
    }
    heap->arr = new_arr;
    heap->capacity = new_cap;
  }
  heap->arr[heap->size] = p;
  heapify_up(heap, heap->size);
  heap->size++;
}

Process *heap_pop(MinHeap *heap) {
  if (!heap || heap->size == 0)
    return NULL;
  Process *root = heap->arr[0];
  heap->size--;
  heap->arr[0] = heap->arr[heap->size];
  heapify_down(heap, 0);
  return root;
}

int heap_is_empty(MinHeap *heap) { return (heap == NULL || heap->size == 0); }

void free_heap(MinHeap *heap) {
  if (heap) {
    free(heap->arr);
    free(heap);
  }
}
