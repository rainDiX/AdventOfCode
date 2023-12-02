#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
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
  const std::string digits[] = {"one", "two",   "three", "four", "five",
                                "six", "seven", "eight", "nine"};

  while (std::getline(infile, line)) {
    int first = 0, last = 0, i = 0;

    do {
      char c = line[i];
      if (isdigit(c)) {
        first = c - '0';
      } else {
        for (int j = 0; j < 9; ++j) {
          if (line.compare(i, digits[j].length(), digits[j]) == 0) {
            first = j + 1;
            break;
          }
        }
      }
      ++i;
    } while (!first && i < line.length());

    i = line.length() - 1;
    do {
      char c = line[i];
      if (isdigit(c)) {
        last = c - '0';
      } else {
        for (int j = 0; j < 9; ++j) {
          if (line.compare(i, digits[j].length(), digits[j]) == 0) {
            last = j + 1;
            break;
          }
        }
      }
      --i;
    } while (!last && i >= 0);

    sum += first * 10 + last;
  }
  std::cout << "the sum of all of the calibration values is : " << sum << "\n";
  return 0;
}