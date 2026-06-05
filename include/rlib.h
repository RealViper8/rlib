#ifndef _RLIB_H
#define _RLIB_H

#ifdef __cplusplus
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#else
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS_OS 1
#elif defined(__ANDROID__)
#error "Not supported"
#elif defined(__linux__)
#define LINUX_OS 1
#else
#error "Unkown OS"
#endif

#if (WINDOWS_OS)
#include <windows.h>
#include <winnt.h>
#endif

#if (LINUX_OS)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Array {
  void *data;
  uint32_t capacity;
  uint32_t size;
  uint32_t elem_size;

  void (*push)(struct Array *arr, const void *value);
  void *(*get)(struct Array *arr, const uint32_t index);
  void (*resize)(struct Array *arr, uint32_t new_size);
  void (*free)(struct Array *arr);
} array_t;

array_t array(size_t capacity, uint32_t elem_size);

typedef struct {
  /**
   * # Used for writing json data
   * If len is wrong its considered UB
   */
  void (*write_json)(const char *path, char *data, uint32_t len);
} serializer_t;

typedef struct Inj {
  /**
   * # The path relative to the targets exe !!
   */
  const char *shared_path;
  unsigned long pid;
  void (*inject)(struct Inj *);
} injector_t;

injector_t injector(unsigned long pid, const char *shared_path);
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

class Injector {
private:
  injector_t j;

public:
  Injector(const unsigned long pid, std::string &dll_path)
      : j(injector(pid, (char *)dll_path.data())) {}

  void inject() { this->j.inject(&this->j); }

  void set_path(std::string path) { this->j.shared_path = path.c_str(); }
  void set_pid(unsigned long pid) { this->j.pid = pid; }
};

#endif

#endif
