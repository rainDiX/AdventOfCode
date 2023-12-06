#pragma once

#include <functional>
#include <charconv>
#include <string_view>
#include <vector>

template <typename T>
concept NumericType= std::integral<T> || std::floating_point<T>;

void strSplit(const std::string_view str, const std::string_view delimiter,
              std::vector<std::string_view>& vec);

template <typename T>
void forEachNumber(std::string_view str, std::function<void(T)> apply) {
  size_t pos = 0;
  while (pos < str.size()) {
    size_t size = 0;
    while (std::isdigit(str[pos + size])) {
      ++size;
    }
    if (size > 0) {
      auto numStr = str.substr(pos, size);
      T num;
      std::from_chars(numStr.begin(), numStr.end(), num);
      apply(num);
    }
    pos += size + 1;
  }
}
