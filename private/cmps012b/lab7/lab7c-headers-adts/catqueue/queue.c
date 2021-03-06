// $Id: queue.c,v 1.10 2014-02-27 12:12:24-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

typedef struct queue_node queue_node;
struct queue_node {
   queue_item_t item;
   queue_node *link;
};

struct queue {
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
   STUBPRINTF ("return NULL\n");
   return NULL;
}

void free_queue (queue *this) {
   assert (isempty_queue (this));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
   STUBPRINTF ("item = \"%s\"\n", item);
}

queue_item_t remove_queue (queue *this) {
   assert (! isempty_queue (this));
   STUBPRINTF ("return NULL\n");
   return NULL;
}

bool isempty_queue (queue *this) {
   return this->front == NULL;
}

