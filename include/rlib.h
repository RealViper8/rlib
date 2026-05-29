#ifndef _RLIB_H
#define _RLIB_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  Windows,
  Linux,
} target;

#if defined(_WIN32) || defined(_WIN64)
#define OS Windows
#elif defined(__ANDROID__)
#error "Not supported"
#elif defined(__linux__)
#define OS Linux
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  /**
   * # Used for writing json data
   * If len is wrong its considered UB
   */
  void (*write_json)(const char *path, char *data, size_t len);
} serializer_t;

serializer_t serializer();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

class Serializer {
private:
  std::string path;
  serializer_t s;

public:
  Serializer(const std::string path) : path(path), s(serializer()) {}

  void write_json(const std::string &data, size_t len) {
    this->s.write_json(this->path.c_str(), (char *)std::data(data), len);
  }

  void write_json(std::string data, const std::string path, size_t len) {
    this->path = path;
    this->s.write_json(this->path.c_str(), (char *)std::data(data), len);
  }
};

#endif

#endif
