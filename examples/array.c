#include "rlib.h"
#include <assert.h>
#include <stdio.h>

int main() {
  array_t arr = array(4, sizeof(char *));
  arr.push(&arr, "Hello");
  arr.push(&arr, "World");
  arr.push(&arr, "!");

  assert(arr.size == 3);
  assert(arr.capacity == 4);

  for (size_t i = 0; i < arr.size; i++) {
    printf("%zu: %s\n", i, (char *)arr.get(&arr, i));
    fflush(stdout);
  }

  arr.free(&arr);
  return 0;
}
