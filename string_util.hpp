#pragma once

#include <string>
#include <cstring>

class StringStream {
  std::string s_;

public:
  void write(const char* src, size_t length) {
    s_.append(src, length);
  }

  void write(const char* src) {
    write(src, std::strlen(src));
  }

  size_t length() const {
    return s_.size();
  }

  const char* data() const {
    return s_.c_str();
  }

  void read(char* dest, size_t n) const {
    size_t size = n < length() ? n + 1 : length() + 1;
    std::memcpy(dest, data(), size);
  }

  void read(char* dest) const {
    std::memcpy(dest, data(), length() + 1);
  }
};

void concat_strings(char* dest) {
  dest[0] = '\0';
}
template <class... Ts>
void concat_strings(char* dest, const char* src, Ts... srcs) {
  size_t length = std::strlen(src);
  memcpy(dest, src, length);
  concat_strings(dest + length, srcs...);
}


