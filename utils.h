#ifndef QUEUE_H
#define QUEUE_H

#include "Scheduling_Algorithms/Algorithms.h" // This defines Process fully

typedef struct Process Process;
typedef struct QueueNode {
  Process *process;
  struct QueueNode *next;
} QueueNode;

typedef struct {
  QueueNode *front;
  QueueNode *rear;
  int size;
} Queue;

Queue *create_queue(void);
bool is_empty(Queue *q);
void enqueue(Queue *q, Process *process);
Process *dequeue(Queue *q);
Process *peek(Queue *q);
int queue_size(Queue *q);
void display_queue(Queue *q);
void free_queue(Queue *q);

// -------utils: print helper
void print_results(Process p[], int n, char *def);

// --------Priorty queue

typedef struct {
  Process **arr; // array of Process pointers
  int size;      // current number of elements
  int capacity;  // allocated size
} MinHeap;

// Create a new min‑heap with given initial capacity
MinHeap *create_heap(int capacity);

// Insert a process into the heap (ordered by bt, then at)
void heap_push(MinHeap *heap, Process *p);

// Remove and return the process with smallest bt (and earliest at if tie)
Process *heap_pop(MinHeap *heap);

// Check if the heap is empty
int heap_is_empty(MinHeap *heap);

// Free all memory used by the heap
void free_heap(MinHeap *heap);

#endif
