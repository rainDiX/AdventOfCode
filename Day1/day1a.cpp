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
  while (std::getline(infile, line)) {
    int first = 0, last = 0, i = 0;

    do {
      char c = line[i];
      if (isdigit(c)) {
        first = c - '0';
      }
      ++i;
    } while (!first && i < line.length());

    i = line.length() - 1;
    do {
      char c = line[i];
      if (isdigit(c)) {
        last = c - '0';
      }
      --i;
    } while (!last && i >= 0);

    sum += first * 10 + last;
  }
  std::cout << "the sum of all of the calibration values is : " << sum << "\n";
  return 0;
}