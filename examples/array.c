#include "rlib.h"
#include <assert.h>
#include <stdio.h>

int main() {
  // Array
  // 0: Hello
  // 1: World
  // capacity: 2
  array_t arr = array(2, sizeof(char *));
  arr.push(&arr, "Hello");
  arr.push(&arr, "World");
  arr.resize(&arr, 3);
  arr.push(&arr, "!");
  // Array
  // 0: Hello
  // 1: World
  // 2: !
  // capacity: 3

  assert(arr.size == 3);
  assert(arr.capacity == 3);

  // Array
  // 0: Hello
  // 1: World
  // 2: !
  // capacity: 3
  for (size_t i = 0; i < arr.size; i++) {
    printf("%zu: %s\n", i, (char *)arr.get(&arr, i));
    fflush(stdout);
  }

  putc('\n', stdout);

  // Array
  // 0: Hello
  // 1: World
  // capacity: 2
  arr.resize(&arr, 2);
  for (size_t i = 0; i < arr.size; i++) {
    printf("%zu: %s\n", i, (char *)arr.get(&arr, i));
    fflush(stdout);
  }

  assert(arr.size == 2);
  assert(arr.capacity == 2);

  arr.free(&arr);
  return 0;
}
