//Manav Sharma msharma7
//Christian Lam ctlam

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include "strhash.h"

size_t strhash (char *string){
    assert (string != NULL);
    size_t hashcode= 0;
    while (*string) hashcode = (hashcode <<5) - hashcode + *string++;
    return hashcode;
}
