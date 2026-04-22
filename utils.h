#ifndef UTILS_H
#define UTILS_H

#include "process.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Queue structure
typedef struct QueueNode {
  Process *process;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
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

// MinHeap structure
typedef struct MinHeap {
  Process **arr;
  int size;
  int capacity;
} MinHeap;

MinHeap *create_heap(int capacity);
void heap_push(MinHeap *heap, Process *p);
Process *heap_pop(MinHeap *heap);
int heap_is_empty(MinHeap *heap);
void free_heap(MinHeap *heap);

// Printing helper
void print_results(Process p[], int n, const char *def);

#endif
