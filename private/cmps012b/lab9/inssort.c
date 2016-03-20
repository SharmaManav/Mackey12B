//Manav Sharma msharma7
//Christian Lam ctlam

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inssort.h"

void inssort(void *base, size_t num, size_t size,
             int (*check) (const void *, const void*)){

    for (size_t i = 1; i<num; i++){
    size_t slot = i;
    void *array_slot = base + slot*size;
    void *copy = malloc(size);
    memcpy(copy, array_slot, size);
    for (; array_slot > base; array_slot -= size){
        int comp = check(copy, array_slot - size);
        if (comp > 0) break;
        memcpy(array_slot, array_slot - size, size);
    }
    memcpy(array_slot, copy, size);
    free(copy);
    }
}
