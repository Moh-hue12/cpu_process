#include "utils.h"
#include <stdlib.h>

Queue *create_queue(void) {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  if (q == NULL) {
    printf("Failed to allocate queue\n");
    return NULL;
  }
  q->front = NULL;
  q->rear = NULL;
  q->size = 0;
  return q;
}

bool is_empty(Queue *q) { return (q == NULL || q->front == NULL); }

void enqueue(Queue *q, Process *process) {
  if (q == NULL)
    return;

  QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
  if (new_node == NULL) {
    printf("Failed to allocate queue node\n");
    return;
  }
  new_node->process = process;
  new_node->next = NULL;

  if (q->rear == NULL) {
    q->front = new_node;
    q->rear = new_node;
  } else {
    q->rear->next = new_node;
    q->rear = new_node;
  }
  q->size++;
}

Process *dequeue(Queue *q) {
  if (q == NULL || is_empty(q)) {
    return NULL;
  }

  QueueNode *temp = q->front;
  Process *process = temp->process;

  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }

  free(temp);
  q->size--;
  return process;
}

Process *peek(Queue *q) {
  if (q == NULL || is_empty(q)) {
    return NULL;
  }
  return q->front->process;
}

int queue_size(Queue *q) { return (q == NULL) ? 0 : q->size; }

// Display all process IDs in the queue
void display_queue(Queue *q) {
  if (q == NULL || is_empty(q)) {
    printf("Queue is empty\n");
    return;
  }

  QueueNode *current = q->front;
  printf("Queue (front to rear): ");
  while (current != NULL) {
    printf("[P%d] ", current->process->id);
    current = current->next;
  }
  printf("\n");
}

void free_queue(Queue *q) {
  if (q == NULL)
    return;
  while (!is_empty(q)) {
    dequeue(q);
  }
  free(q);
}
