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
