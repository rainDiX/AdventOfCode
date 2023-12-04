#include <charconv>
#include <expected>
#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

#include "commonIO.hpp"

class TextMatrix {
 public:
  TextMatrix(std::string& text) : m_data(text) { init(); }
  TextMatrix(std::string&& text) : m_data(text) { init(); }

  const char& operator[](size_t row, size_t col) const {
    if (row > m_height || col > m_width) {
      throw std::out_of_range{"out of bound access"};
    }
    return m_data[row * (m_width + 1) + col];
  }

  const std::string_view substr(size_t row, size_t col, size_t size) const {
    return std::string_view(m_data).substr(row * (m_width + 1) + col, size);
  }

  const std::string_view data() const { return m_data; }
  size_t width() const { return m_width; }
  size_t height() const { return m_height; }

 private:
  void init() {
    m_width = m_data.find('\n');
    m_height = m_data.size() / (m_width + 1);
  }

  std::string m_data;
  size_t m_width;
  size_t m_height;
};

bool symbolsInNeighborhood(const TextMatrix& schematic, size_t row, size_t col, size_t str_witdh) {
  int startRow = row > 0 ? row - 1 : row;
  int startCol = col > 0 ? col - 1 : col;
  int stopRow = row < schematic.height() - 1 ? row + 1 : row;
  int stopCol = col + str_witdh < schematic.width() - 1 ? col + str_witdh : col + str_witdh - 1;
  bool res = false;

  int i = startRow;
  while (i <= stopRow && !res) {
    int j = startCol;
    while (j <= stopCol && !res) {
      char current = schematic[i, j];
      res = current != '.' && !std::isdigit(current);
      ++j;
    }
    ++i;
  }
  return res;
}

int part1(const TextMatrix& schematic, size_t row, size_t col, size_t size) {
  int res = 0;
  if (symbolsInNeighborhood(schematic, row, col, size)) {
    auto num_str = schematic.substr(row, col, size);
    std::from_chars(num_str.begin(), num_str.end(), res);
  };
  return res;
}

void getFullNumber(const TextMatrix& schematic, size_t row, size_t col, size_t& begin,
                   size_t& size) {
  begin = col;
  while (begin > 0 && (std::isdigit(schematic[row, begin - 1]))) {
    --begin;
  }
  auto end = col;
  while (end < schematic.width() && (std::isdigit(schematic[row, end + 1]))) {
    ++end;
  }
  size = end - begin + 1;
}

int gearRatio(const TextMatrix& schematic, size_t row, size_t col) {
  int startRow = row > 0 ? row - 1 : row;
  int startCol = col > 0 ? col - 1 : col;
  int stopRow = row < schematic.height() - 1 ? row + 1 : row;
  int stopCol = col < schematic.width() - 1 ? col + 1 : col;
  int neighborCount = 0;
  int ratio = 1;

  int i = startRow;
  while (i <= stopRow && neighborCount <= 2) {
    int j = startCol;
    while (j <= stopCol && neighborCount <= 2) {
      size_t begin = j, size = 0;
      int num;
      if (std::isdigit(schematic[i, j])) {
        if (neighborCount < 2) {
          getFullNumber(schematic, i, j, begin, size);
          auto num_str = schematic.substr(i, begin, size);
          std::from_chars(num_str.begin(), num_str.end(), num);
          ratio *= num * (neighborCount <= 2);
        }
        ++neighborCount;
      }
      j = begin + size + 1;
    }
    ++i;
  }
  return ratio * (neighborCount == 2);
}

int main(int argc, char* argv[]) {
  std::filesystem::path path{"./Day3/input"};
  if (argc == 2) {
    path = std::filesystem::path(argv[1]);
  }

  auto schematic_txt = *readFileC(path);
  auto schematic = TextMatrix{std::move(schematic_txt)};

  int sum_part1 = 0, sum_part2 = 0;
  size_t i = 0;
  while (i < schematic.height()) {
    size_t j = 0;
    while (j < schematic.width()) {
      int size = 0;
      while (j + size < schematic.width() && std::isdigit(schematic[i, j + size])) {
        ++size;
      }
      if (size > 0) {
        sum_part1 += part1(schematic, i, j, size);
        j += size;
      } else {
        if (schematic[i, j] == '*') {
          sum_part2 += gearRatio(schematic, i, j);
        }
        ++j;
      }
    }
    ++i;
  }

  std::cout << "1: The sum of all of the part numbers is " << sum_part1 << "\n";
  std::cout << "2: the sum of all of the gear ratios is " << sum_part2 << "\n";

  return 0;
}