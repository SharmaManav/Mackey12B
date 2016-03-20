// $Id: list4.c,v 1.4 2016-02-10 21:35:24-08 - - $
// Manav Sharma msharma7 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
   char *word;
   node *link;
   node *head;
};

int main (int argc, char **argv) {
   node *head = NULL;
   for (int argi = 0; argi < 5; ++argi) {
      node *node = malloc (sizeof (struct node));
      assert (node != NULL);
      node->word = argv[argi];
      node->link = head;
      head = node;
   }
   for (node *curr = head; curr->link != NULL; curr = curr->link) {
      printf ("%p->node {word=%p->[%s], link=%p}\n",
              curr, curr->word, curr->word, curr->link);
   }
   while (head!=NULL){
     node *old = head;
     head=head->link;
     free(old);
    }
        return EXIT_SUCCESS;
}

