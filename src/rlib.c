#define _CRT_SECURE_NO_WARNINGS
#include "rlib.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void array_free(array_t *arr) {
  free(arr->data);
  arr->data = NULL;
}

void *array_get(array_t *arr, const size_t i) {
  return (char *)arr->data + i * arr->elem_size;
}

/// If the new_size is < than length it will strip the remains
void array_resize(struct Array *arr, size_t new_size) {
  arr->data = realloc(arr->data, new_size * arr->elem_size);

  if (arr->size > new_size) {
    arr->capacity = new_size;
    arr->size = new_size;
  } else
    arr->capacity = new_size;
}

void array_push(array_t *arr, const void *value) {
  if (arr->size >= arr->capacity) {
    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->elem_size * arr->capacity);
  }
  memcpy((char *)arr->data + arr->size++ * arr->elem_size, value,
         arr->elem_size);
}

array_t array(size_t capacity, size_t elem_size) {
  if (capacity < 1) {
    capacity = 1;
  }

  array_t arr = {0};
  arr.get = array_get;
  arr.push = array_push;
  arr.resize = array_resize;
  arr.free = array_free;
  arr.data = calloc(capacity, elem_size);
  arr.size = 0;
  arr.capacity = capacity;
  arr.elem_size = elem_size;
  return arr;
}

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

#if (OS == 0)
void inject(injector_t *j) {
  HANDLE processHandle;
  PVOID remoteBuffer;

  processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, j->pid);
  if (!processHandle) {
    printf("OpenProcess failed: %lu\n", GetLastError());
    return;
  }

  size_t pathSize = (strlen(j->shared_path) + 1);
  remoteBuffer =
      VirtualAllocEx(processHandle, NULL, pathSize, MEM_COMMIT, PAGE_READWRITE);
  if (!remoteBuffer) {
    printf("VirtualAllocEx failed: %lu\n", GetLastError());
    return;
  }
  WriteProcessMemory(processHandle, remoteBuffer, j->shared_path, pathSize,
                     NULL);
  PTHREAD_START_ROUTINE routine = (PTHREAD_START_ROUTINE)GetProcAddress(
      GetModuleHandle("Kernel32"), "LoadLibraryA");
  CreateRemoteThread(processHandle, NULL, 0, routine, remoteBuffer, 0, NULL);
  CloseHandle(processHandle);
}
#endif

injector_t injector(unsigned long pid, const char *dll_path) {
  injector_t j = {0};
  j.pid = pid;
  j.shared_path = dll_path;
  j.inject = inject;
  return j;
}

/**
 * Creates a new Serializer
 */
serializer_t serializer() {
  serializer_t s = {0};
  s.write_json = write_json;
  return s;
}
