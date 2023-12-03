#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

int find_digit(std::string_view line, int pos, std::function<bool(int)> cond,
               std::function<void(int&)> step) {
  int res = 0;
  do {
    char c = line[pos];
    if (isdigit(c)) {
      res = c - '0';
    }
    step(pos);
  } while (!res && cond(pos));
  return res;
}

int find_digit_v2(std::string_view line, int pos, std::function<bool(int)> cond,
                  std::function<void(int&)> step) {
  const std::string_view digits[] = {"one", "two",   "three", "four", "five",
                                     "six", "seven", "eight", "nine"};
  int res = 0;
  do {
    char c = line[pos];
    if (isdigit(c)) {
      res = c - '0';
    } else {
      for (int j = 0; j < 9; ++j) {
        if (line.compare(pos, digits[j].length(), digits[j]) == 0) {
          res = j + 1;
          break;
        }
      }
    }
    step(pos);
  } while (!res && cond(pos));
  return res;
}

int main(int argc, char* argv[]) {
  std::filesystem::path path{"./Day1/input"};

  if (argc == 2) {
    path = std::filesystem::path(argv[1]);
  }

  if (!std::filesystem::exists(path)) {
    std::cerr << "File not found: " << path << std::endl;
    return 1;
  }

  std::ifstream infile{path};
  std::string line;
  int sum = 0;
  int sum_v2 = 0;
  while (std::getline(infile, line)) {
    const auto length = line.length();

    int first = find_digit(
        line, 0, [length](int i) { return i < length; }, [](int& i) { ++i; });

    int last = find_digit(
        line, length - 1, [](int i) { return i >= 0; }, [](int& i) { --i; });

    int first_v2 = find_digit_v2(
        line, 0, [length](int i) { return i < length; }, [](int& i) { ++i; });

    int last_v2 = find_digit_v2(
        line, length - 1, [](int i) { return i >= 0; }, [](int& i) { --i; });

    sum += first * 10 + last;
    sum_v2 += first_v2 * 10 + last_v2;
  }
  std::cout << "1: the sum of all of the calibration values is : " << sum << "\n";
  std::cout << "2: the sum of all of the calibration values is : " << sum_v2 << "\n";
  return 0;
}