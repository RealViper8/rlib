#define _CRT_SECURE_NO_WARNINGS
#include "rlib.h"
#include <stdio.h>

void s_write(FILE *file, void *data) {
  if (file == NULL)
    file = fopen("data", "w");

  fwrite(data, sizeof(data), 1, file);
  fflush(file);
  fclose(file);
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

deserializer_t deserializer(void *buffer) {
  deserializer_t d = {0};
  d.buffer = buffer;
  return d;
}
