#ifndef _RLIB_H
#define _RLIB_H

#include <stdint.h>
#include <stdio.h>

typedef struct Serializer {
  /**
   * file: File Handle
   * data: Data to save
   */
  void (*write)(FILE *file, char *data);
  void (*write_json)(FILE *file, char *data, size_t len);
} serializer_t;

typedef struct Deserializer {
  void *buffer;
} deserializer_t;

serializer_t serializer();
deserializer_t deserializer(void *buffer);

#endif
