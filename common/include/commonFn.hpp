#pragma once

#include <charconv>
#include <functional>
#include <string_view>
#include <vector>

void strSplit(const std::string_view str, const std::string_view delimiter,
              std::vector<std::string_view>& vec);

void forEachNumber(std::string_view str, std::function<void(int)> reduce);