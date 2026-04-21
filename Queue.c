#include "utils.h"

// Create a new empty queue
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

// Check if queue is empty
bool is_empty(Queue *q) { return (q == NULL || q->front == NULL); }

// Add a process to the rear of the queue
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

// Remove and return the front process
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

// Return front process without removing it
Process *peek(Queue *q) {
  if (q == NULL || is_empty(q)) {
    return NULL;
  }
  return q->front->process;
}

// Return current queue size
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

// Free all memory used by the queue
void free_queue(Queue *q) {
  if (q == NULL)
    return;
  while (!is_empty(q)) {
    dequeue(q);
  }
  free(q);
}
