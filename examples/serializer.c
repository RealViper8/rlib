#define _CRT_SECURE_NO_WARNINGS
#include "rlib.h"
#include <stdio.h>

int main() {
  FILE *f = fopen("test.json", "w");
  serializer_t s = serializer();
  char data[] = "\"key\"=123,\"test\"=\"hallozusammen\"";
  s.write_json(f, data, 3);

  return 0;
}
