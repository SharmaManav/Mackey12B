// $Id: bigint.c,v 1.15 2015-02-03 18:11:58-08 - - $

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "debug.h"

#define MIN_CAPACITY 16

struct bigint {
   size_t capacity;
   size_t size;
   bool negative;
   char *digits;
};

void trim_zeros (bigint *this) {
   while (this->size > 0) {
      size_t digitpos = this->size - 1;
      if (this->digits[digitpos] != 0) break;
      --this->size;
   }
}

bigint *new_bigint (size_t capacity) {
   bigint *this = malloc (sizeof (bigint));
   assert (this != NULL);
   this->capacity = capacity;
   this->size = 0;
   this->negative = false;
   this->digits = calloc (this->capacity, sizeof (char));
   assert (this->digits != NULL);
   DEBUGS ('b', show_bigint (this));
   return this;
}


bigint *new_string_bigint (const char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   const char *strdigit = &string[length - 1];
   if (*string == '_') {
      this->negative = true;
      ++string;
   }
   char *thisdigit = this->digits;
   while (strdigit >= string) {
      assert (isdigit (*strdigit));
      *thisdigit++ = *strdigit-- - '0';
   }
   this->size = thisdigit - this->digits;
   trim_zeros (this);
   DEBUGS ('b', show_bigint (this));
   return this;
}

bigint *do_add (bigint *this, bigint *that) {
   int digit = 0;
   int carry = 0;
   int thisValue = 0;
   int thatValue = 0;

   bigint *result = new_bigint(this->size+1);
   result->size = this->size+1;

   for (int i = 0; i <=(int)(result->size); i++){
     if ((int)(this->size-1) < i) thisValue = 0;
     else thisValue = this->digits[i];

     if ((int)(that->size-1) < i) thatValue = 0;
     else thatValue = that->digits[i];

     digit = thatValue + thisValue + carry;
     result->digits[i] = digit % 10;
     carry = digit/10;
   }
     trim_zeros(result);
     return result;
}

bigint *do_sub (bigint *this, bigint *that) {
   int digit = 0;
   int borrow = 0;
   int thisValue = 0;
   int thatValue = 0;

   bigint *result = new_bigint(this->size+1);
   result->size = this->size+1;

   for (int i = 0; i < (int)(result->size); i++){
      if ((int)(this->size-1)<i) thisValue = 0;
      else thisValue = this->digits[i];

      if ((int)that->size-1<i) thatValue = 0;
      else thatValue = that->digits[i];

      digit = thisValue - thatValue - borrow + 10;
      result->digits[i] = digit % 10;
      borrow = 1 - digit/10;
  }

  trim_zeros(result);
  return result;

}
void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

void print_bigint (bigint *this, FILE *file) {
   int cg = 69;
   int printNow = 0;

   if (this == NULL) {
      fprintf(file, "mydc: bigint@%p is empty", this);
      return;
    }

   if (this->negative) {
       fprintf(file,"-");
       printNow++;
   }
    
   for (int index = this->size -1; index >= 0; index--){
     fprintf(file, "%d", this->digits[index]);
     printNow++;
     if (printNow >= cg){
        fprintf(file,"\\\n");
        printNow = 0;
        }
    }
    fprintf(file,"\n");
}

bigint *add_bigint (bigint *this, bigint *that) {
   bigint *max = NULL;
   bigint *min = NULL;
   bigint *result = NULL;

   if (this->size > that->size) {
        max = this;
        min = that;
   }else{
        max = that;
        min = this;
   }

  if (this->negative == that->negative){
     result = do_add(max,min);
  }else{
    result = do_sub(max,min);
  }

  result->negative = max->negative;
  return result;
}

bigint *sub_bigint (bigint *this, bigint *that) {
   bigint *max = NULL;
   bigint *min = NULL;
   bigint *result = NULL;
   if (this->size > that->size) {
       max = this;
       min = that;
   }else{
       max = that;
       min = this;
   }
   if(this->negative == that->negative){
       result = do_add(max,min);
   }else{
       result = do_sub(max,min);
   }

   result->negative = max->negative;
   return result;
}


bigint *mul_bigint (bigint *this, bigint *that) {
    int carry = 0;
    int digit = 0;
    bigint *final = new_bigint(this->size + that->size);
    final->size = this->size + that->size;
    for (int i = 0; i<(int)(this->size); i++){
        carry - 0;
          for (int x = 0; x<(int)(that->size); x++){
          digit = final->digits[i+x]+this->digits[i]*that->digits[x]+carry;
          final->digits[i+x] = digit%10;
          carry = digit/10;
          }
    final->digits[i+that->size] = carry; 
   }
   trim_zeros(final);
   if (this->negative != that->negative){
       final->negative = true;
   }
   return final;
}

void show_bigint (bigint *this) {
   fprintf (stderr, "bigint@%p->{%lu,%lu,%c,%p->", this,
            this->capacity, this->size, this->negative ? '-' : '+',
            this->digits);
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte) {
      fprintf (stderr, "%d", *byte);
   }
   fprintf (stderr, "}\n");
}

