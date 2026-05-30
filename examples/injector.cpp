#include "rlib.h"
#include <string>

int main() {
  // Relative path is targets .exe
  // so better specify whole path
  // std::string path_eg("B:\\rlib\\msg.dll");
  std::string path("<yourpath>");
  auto j = Injector(7248, path);
  j.inject();
  return 0;
}
