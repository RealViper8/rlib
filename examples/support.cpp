#include <rlib.h>

int main() {
  // Creating serializer c++ obj
  Serializer s = Serializer("test.json");
  s.write_json("\"token\"=0xFF,\"username\"=\"nig\"", 2);
  return 0;
}
