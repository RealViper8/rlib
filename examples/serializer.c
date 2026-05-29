#define _CRT_SECURE_NO_WARNINGS
#include "rlib.h"

int main() {
  serializer_t s = serializer();
  char data[] = "\"key\"=123,\"test\"=\"hallozusammen\"";
  s.write_json("test.json", data, 2);
  return 0;
}
