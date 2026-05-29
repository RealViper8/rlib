#define _CRT_SECURE_NO_WARNINGS
#include "rlib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_json(const char *path, char *data, size_t len) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    perror(NULL);
    return;
  }

  char *key = strtok(data, "=");
  char *val = strtok(NULL, ",");

  fputs("{\n", file);

  for (size_t i = 0; i < len; i++) {
    fputs("  ", file);
    fwrite(key, sizeof(char), strlen(key), file);
    fputc(':', file);
    fputc(' ', file);
    fwrite(val, sizeof(char), strlen(val), file);
    if (i != len - 1) {
      fputc(',', file);
      fputc('\n', file);
    }
    key = strtok(NULL, "=");
    val = strtok(NULL, ",");
  }

  fputs("\n}", file);
  fflush(file);
  fclose(file);
}

/**
 * Creates a new Serializer
 */
serializer_t serializer() {
  serializer_t s = {0};
  s.write_json = write_json;
  return s;
}
