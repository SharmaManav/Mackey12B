//Manav Sharma msharma7
//Christian Lam ctlam

#ifndef __INSSORT_H__
#define __INSSORT_H__
#include <stdio.h>

void inssort (void *base, size_t num, size_t size,
              int(*check) (const void*, const void*));

#endif
