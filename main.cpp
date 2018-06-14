#include <iostream>
#include <cstdlib>

#include "symbols.hpp"

enum DataType {
  TYPE_DATA,
  TYPE_CELL,
  TYPE_SYMBOL,
  TYPE_STRING
};

struct Data {
  DataType type;
};

class Ptr {
  Data* raw;

public:
  Ptr() : raw(nullptr) {}
  Ptr(Data* raw) : raw(raw) {}
  
  Data& operator*() const { return *raw; }
  Data* operator->() const { return raw; }

  template<class T>
  T* as() const {
    return (T*)raw;
  }

  template<class T>
  T& deref() const {
    return *as<T>();
  }
};

struct Cell : Data {
  Ptr car, cdr;
};

struct Symbol : Data {
  const char* value;
};

struct String : Data {
  const char* data;
  size_t length;
};

template <class T>
Ptr data_alloc() {
  return new T;
}

template <class T, class... Args>
Ptr make_data(Args... args) {
  Ptr p = data_alloc<T>();
  p.deref<T>() = T{args...};
  return p;
}

Ptr make_string(const char* s) {
  return make_data<String>(TYPE_STRING, s, std::strlen(s));
}

Ptr display(Ptr data) {
  switch (data->type) {
    case TYPE_DATA:
      return make_string("<Data>");

    case TYPE_CELL:
      return make_string("<Cell>");

    case TYPE_SYMBOL:
      return make_string(data.as<Symbol>()->value);

    case TYPE_STRING:
      return data; //fixme
  }
}

void print(Ptr data) {
  std::cout << display(data).deref<String>().data;
}

void println(Ptr data) {
  print(data);
  std::cout << std::endl;
}

int main() {
  println(make_data<Symbol>(TYPE_SYMBOL, "symbol"));
  return 0;
}
