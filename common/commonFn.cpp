#include "commonFn.hpp"

#include <string>

void strSplit(const std::string_view str, const std::string_view delimiter,
              std::vector<std::string_view>& vec) {
  size_t begin = 0, end = 0;
  while ((end = str.find(delimiter, begin)) != std::string::npos) {
    vec.push_back(str.substr(begin, end - begin));
    begin = end + delimiter.size();
  }
  vec.push_back(str.substr(begin));
}
