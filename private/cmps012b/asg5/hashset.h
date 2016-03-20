//Manav Sharma msharma7
//Christian Lam ctlam

#ifndef __HASHSET_H__
#define __HASHSET_H__
#include <stdbool.h>

typedef struct hashset hashset;

hashset *new_hashset (void);

void free_hashset(hashset *);

void double_hash(hashset *);

void put_hashset(hashset *, char*);

bool has_hashset(hashset *, char*);

void cluster_print(hashset *);

void hash_dump(hashset *);
#endif
