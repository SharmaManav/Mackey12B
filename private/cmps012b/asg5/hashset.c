//Manav Sharma msharma7
//Christian Lam ctlam

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

typedef struct hashnode hashnode;
typedef size_t hashcode_t;
struct hashnode {
  char *word;
  hashnode *link;
};

struct hashset {
  size_t size;
  size_t load;
  hashnode **chains;
};

hashset *new_hashset (void) {
  hashset *this = malloc (sizeof (struct hashset));
  assert (this != NULL);
  this->size = HASH_NEW_SIZE;
  this->load = 0;
  size_t sizeof_chains = this->size * sizeof (hashnode *);
  this->chains = malloc (sizeof_chains);
  assert (this->chains != NULL);
  memset (this->chains, 0, sizeof_chains);
  return this;
}

void free_hashset (hashset *this) {
  for(size_t index = 0; index < this->size; index++){
    hashnode *tmp = this->chains[index];
    while(tmp != NULL){
      hashnode *next = tmp->link;
      free(tmp->word);
      free(tmp);
      tmp = next;
    }
  }
  free(this->chains);
  free(this);
}

void double_hash(hashset *this){
  size_t newsize = this->size * 2 + 1;
  hashnode **new_chain = calloc(newsize, sizeof(hashnode *));
  for(size_t index = 0; index < this->size; index++){
    hashnode *tmp = this->chains[index];
    while (tmp != NULL){
      hashcode_t hash_index = strhash (tmp->word) % newsize;
      hashnode *link = tmp->link;
      tmp->link = new_chain[hash_index];
      new_chain[hash_index] = tmp;
      tmp = link; 
    } 
  }
  free(this->chains);
  this->chains = new_chain;
  this->size = newsize;
}

void put_hashset (hashset *this, char *item) {
  this->load++; 
  if (this->load * 2 > this->size){
    double_hash (this);
  }
  hashcode_t hash_index = strhash (item) % this->size;
  hashnode *curr = this->chains[hash_index];
  for(; curr != NULL; curr = curr->link){
    if (strcmp(curr->word, item) == 0) return;
  }
  hashnode *new = malloc(sizeof (struct hashnode));
  new->link = this->chains[hash_index];
  new->word = strdup(item);
  this->chains[hash_index] = new;
}

bool has_hashset (hashset *this, char *item) {
  hashcode_t hash_index = strhash (item) % this->size;
  hashnode *head = this->chains[hash_index];
  for (;head != NULL;  head = head->link){
    if(strcmp(head->word, item) == 0) return true;
  } 
  return false;
}

void cluster_print (hashset *this){
  printf("%d words in the hash set\n", (int)this->load);
  printf("%d size of the hash array\n", (int) this->size);
  int *chaincounts = calloc(100, sizeof(int));
  for(size_t index = 0; index < this->size; index++){
    hashnode *head = this->chains[index];
    int chain_index = 0;
    for(; head != NULL; head = head->link) chain_index++;
    chaincounts[chain_index]++;
  }
  for(int index = 1; index < 100; index++){
    if(chaincounts[index] != 0){
      printf("%5d chains of size %d\n", chaincounts[index], index);
    }
  }
  free(chaincounts);
}

void hash_dump(hashset *this){
  for(size_t index = 0; index < this->size; index++){
    hashnode *tmp = this->chains[index];
    if(tmp != NULL){
      hashcode_t code = strhash(tmp->word);
      printf("array[%10d] = %12u \"%s\"\n",
             (int)index, (int)code, tmp->word);
      tmp = tmp->link;
    }
    while(tmp != NULL){
      hashcode_t code = strhash(tmp->word);
      printf("%18s= %12u \"%s\"\n", "" , (int)code, tmp->word);
      tmp = tmp->link;
    }
  }
}

