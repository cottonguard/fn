#include <iostream>

#include "symbols.hpp"

struct Data {
};

using Ptr = Data*;

struct Cell : Data {
  Ptr car, cdr;
};

struct Symbol : Data {
  const char* value;
};

struct String : Data {
  char* data;
  size_t length;
};

int main() {
  return 0;
}
