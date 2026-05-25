#ifndef _RLIB_H
#define _RLIB_H

#include <stdio.h>

enum FileType {
  json = 0,
  binary,
  none,
};

typedef struct Serializer {
  enum FileType type;
  void (*write)(FILE *file, void *data);
} serializer_t;

typedef struct Deserializer {
  void *buffer;
  FILE *file;
  enum FileType type;
} deserializer_t;

serializer_t serializer();
deserializer_t deserializer(void *buffer);

#endif
