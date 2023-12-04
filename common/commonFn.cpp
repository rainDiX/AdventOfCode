#include "commonFn.hpp"

void strSplit(const std::string_view str, const std::string_view delimiter,
              std::vector<std::string_view>& vec) {
  size_t begin = 0, end = 0;
  while ((end = str.find(delimiter, begin)) != std::string::npos) {
    vec.push_back(str.substr(begin, end - begin));
    begin = end + delimiter.size();
  }
  vec.push_back(str.substr(begin));
}

void forEachNumber(std::string_view str, std::function<void(int)> apply) {
  size_t pos = 0;
  while (pos < str.size()) {
    size_t size = 0;
    while (std::isdigit(str[pos + size])) {
      ++size;
    }
    if (size > 0) {
      auto numStr = str.substr(pos, size);
      int num;
      std::from_chars(numStr.begin(), numStr.end(), num);
      apply(num);
    }
    pos += size + 1;
  }
}