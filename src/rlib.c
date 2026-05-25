#include "rlib.h"
#include <stdio.h>

void s_write(FILE *file, void *data) {

  if (file == NULL)
    file = fopen();
}

/**
 * Creates a new Serializer
 */
serializer_t serializer() {
  serializer_t s = {0};
  s.write = s_write;
  s.type = none;
  return s;
}

deserializer_t deserializer(void *buffer, FILE *file) {
  deserializer_t d = {0};
  d.buffer = buffer;
  d.file = NULL;
  d.type = none;
  return d;
}
