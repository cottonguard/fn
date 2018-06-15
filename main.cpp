#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

#include "symbols.hpp"
#include "string_util.hpp"

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
  operator bool() const { return raw; }

  template<class T>
  T* as() const {
    return (T*)raw;
  }

  template<class T>
  T& deref() const {
    return *as<T>();
  }
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

struct Cell : Data {
  Ptr car, cdr;
/*
  const char* display_list_items(std::string& s, bool first) const {
    
  }

  const char* display_list() const {
    std::string s;
    s += '(';
    s += display_list_items();
    s += ')';
    return s;
  }
  */
};


struct Symbol : Data {
  const char* value;
};

struct String : Data {
  const char* data;
  size_t length;
  
  static char* alloc_data(size_t n) {
    return (char*)std::malloc(n + 1);
  }

  static void dealloc_data(char* p) {
    std::free(p);
  }

  template <class... Ts>
  static String from(Ts... srcs) {
    size_t length = (0 + ... + std::strlen(srcs));
    char* data = alloc_data(length);
    concat_strings(data, srcs...);
    return { TYPE_STRING, data, length };
  }
};

template <class... Ts>
Ptr make_string(Ts... srcs) {
  Ptr p = data_alloc<String>();
  p.deref<String>() = String::from(srcs...);
  return p;
}

template <class... Ptrs>
Ptr concat(Ptrs... ptrs) {
  Ptr p = data_alloc<String>();
  p.deref<String>() = String::from(ptrs.template as<String>()->data...);
  return p;
} 

const char* display(Ptr data) {
  switch (data->type) {
    case TYPE_DATA:
      return "<Data>";

    case TYPE_CELL:
      return "<Cell>";

    case TYPE_SYMBOL:
      return data.as<Symbol>()->value;

    case TYPE_STRING:
      return data.as<String>()->data; //"data"?
  }
}

void print(Ptr data) {
  std::cout << display(data);
}

void println(Ptr data) {
  print(data);
  std::cout << std::endl;
}

int main() {
  return 0;
}


