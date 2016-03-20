//Manav Sharma msharma7
//Christian Lam ctlam

#include <stdio.h>
#include <stdlib.h>
#include "inssort.h"
#define ARRAY_SIZE 1000

int check(const void *l, const void *r){
    if (*(double*)l <= *(double*)r) return 0;
    return 1;
}

int main() {
    double *array = calloc(ARRAY_SIZE, sizeof(double));
    int num = 0;

    for (int i = 0; i < ARRAY_SIZE; i++){
        if (scanf("%lg", &array[i]) !=1) break;
        num++;
    }
    inssort(array, num, sizeof(double), *check);

    for (int i = 0; i < num; i++){
        printf("%20.15lg\n", array[i]);
    }
    free(array);
}
