#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define RED 12
#define GREEN 13
#define BLUE 14

void strSplit(const std::string_view str, const std::string_view delimiter,
              std::vector<std::string_view>& vec) {
  size_t begin = 0, end = 0;
  while ((end = str.find(delimiter, begin)) != std::string::npos) {
    vec.push_back(str.substr(begin, end - begin));
    begin = end + delimiter.size();
  }
  vec.push_back(str.substr(begin));
}

class Game {
 public:
  Game(const std::string_view gameStr) {
    m_red = 0, m_green = 0, m_blue = 0;

    // cut the game id:
    auto pos = gameStr.find(": ");
    auto idStr = gameStr.substr(0, pos);
    auto setsStr = gameStr.substr(pos + 2);
    std::from_chars(idStr.begin() + 5, idStr.end(), m_id);

    auto sets = std::vector<std::string_view>();
    strSplit(setsStr, "; ", sets);

    for (auto& setStr : sets) {
      auto cubes = std::vector<std::string_view>();
      strSplit(setStr, ", ", cubes);

      for (auto cube : cubes) {
        pos = cube.find(" ");
        int count;
        std::from_chars(cube.begin(), cube.end(), count);
        auto color = cube[pos + 1];

        switch (color) {
          case 'r':
            if (count > m_red) m_red = count;
            break;
          case 'g':
            if (count > m_green) m_green = count;
            break;
          case 'b':
            if (count > m_blue) m_blue = count;
            break;
        }
      }
    }
  }

  inline const int id() { return m_id; }
  inline const int red() { return m_red; }
  inline const int green() { return m_green; }
  inline const int blue() { return m_blue; }

  inline const bool isPossible() { return !(m_red > RED || m_green > GREEN || m_blue > BLUE); }

 private:
  int m_id;
  int m_red;
  int m_green;
  int m_blue;
};

int main(int argc, char* argv[]) {
  std::filesystem::path path{"./Day2/input"};

  if (argc == 2) {
    path = std::filesystem::path(argv[1]);
  }

  if (!std::filesystem::exists(path)) {
    std::cerr << "File not found: " << path << std::endl;
    return 1;
  }

  std::ifstream infile{path};
  std::string line;
  int sum_part1 = 0, sum_part2 = 0;
  while (std::getline(infile, line)) {
    auto game = Game(line);
    if (game.isPossible()) {
      sum_part1 += game.id();
    }
    sum_part2 += game.red() * game.green() * game.blue();
  }
  std::cout << "1: The sum of the IDs of the possible games is : " << sum_part1 << "\n";
  std::cout << "2: The sum of the power of the sets is : " << sum_part2 << "\n";
  return 0;
}