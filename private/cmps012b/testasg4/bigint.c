//Manav Sharma msharma7
//Christian Lam ctlam

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

static void trim_zeros (bigint *this) {
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
   return this;
}

bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   
   char *strdigit = &string[length - 1];
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
   return this;;
}


static bigint *do_add (bigint *this, bigint *that) {
  bigint *largest = (this->size > that->size)? this : that;
  bigint *result = new_bigint(largest->capacity + 1);
  result->size = result->capacity;
  int carry = 0;
  int digit = 0;
  for (size_t index = 0; index < result->capacity; index++){
    digit += carry;
    if (index < this->capacity) digit += this->digits[index];
    if (index < that->capacity) digit += that->digits[index];
    result->digits[index] = digit % 10;
    carry = digit/10;
    digit = 0;
  }
  trim_zeros(result);
  return result;
}


static bigint *do_sub (bigint *this, bigint *that) {
  bigint *result = new_bigint(this->capacity);
  result->size = this->capacity;
  int borrow = 0;
  int digit = 0;
  for (size_t index = 0; index < result->capacity; index++){
    digit = this->digits[index] - borrow + 10;
    if (index < that->capacity) digit -= that->digits[index];
    result->digits[index] = digit % 10;
    borrow = 1 - digit/10;
    digit = 0;
  }
  trim_zeros(result);
  return result;
}


static bool bigger (bigint *this, bigint *that){
  // checks if this is greater based on size
  if (this->size > that->size){
    return true;
  }
  if (that->size > this->size){
    return false;
  }
  for (int i = this->size; i > -1 ; i ++){
    if (this->digits[i] > that->digits[i]) return true;
    if (this->digits[i] < that->digits[i]) return false;
  }
  return true;
}

void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

void print_bigint (bigint *this, FILE *file) {
  if (this->negative) fprintf(file, "-");
  int indexw = 0;
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte, indexw++) {
      fprintf (file, "%d", *byte);
      if(indexw == 68) {
       fprintf(file, "\\\n");
       indexw = -1;
      }
   }
   fprintf(file, "\n");
}

bigint *add_bigint (bigint *this, bigint *that) {
  bigint *result = NULL;
   
  if (this->negative == that->negative){
    result = do_add(this, that);
    result->negative = this->negative;
  } else {
    bigint *max = (bigger (this, that))? this : that;
    bigint *min = (bigger (this, that))? that : this;
    result = do_sub(max, min);
    result->negative = max->negative;
  }
  return result;
}

// manages the subtraction of two bigints
bigint *sub_bigint (bigint *this, bigint *that) {
  bigint *result = NULL;
  if(this->negative != that->negative){
    result = do_add(this, that);
    result->negative = this->negative;
  } else {
    bigint *max = (bigger (this, that))? this : that;
    bigint *min = (bigger (this, that))? that : this;
    result = do_sub(max, min);
    result->negative = (max == that) ? !max->negative : max->negative;
    result->size = result->capacity;
    trim_zeros(result);
  }
  return result;
}

bigint *mul_bigint (bigint *this, bigint *that) {
  bigint *result = new_bigint(this->capacity + that->capacity);
  result->size = result->capacity;
  result->negative = this->negative != that->negative;
  for (size_t index_m = 0; index_m < this->capacity; index_m++){
    int carry = 0;
    for (size_t index_n = 0; index_n < that->capacity; index_n++){
      int digit = result->digits[index_m + index_n];
      digit += this->digits[index_m] * that->digits[index_n];
      digit += carry;
      result->digits[index_m + index_n] = digit % 10;
      carry = digit / 10;
    }
    result->digits[index_m + that->capacity] += carry;
  }
  trim_zeros(result);
  return result;
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

bool is_bigint (bigint *this){
  return this != NULL;
}

