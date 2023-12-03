#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <charconv>

class Game {
 public:
  Game(const std::string_view gameStr) {
    const std::string colors[] = {"red", "green", "blue"};
    m_red = 0, m_green = 0, m_blue = 0;

    // cut the game id:
    auto pos = gameStr.find(": ");
    auto idStr = gameStr.substr(0, pos);
    auto setsStr = gameStr.substr(pos + 2);
    std::from_chars(idStr.begin(), idStr.end(), m_id);

    auto sets = std::vector<std::string_view>();
    strToVec(setsStr, "; ", sets);

    for (auto& setStr : sets) {
      auto cubes = std::vector<std::string_view>();
      strToVec(setStr, ", ", cubes);

      for (auto& cube : cubes) {
        pos = cube.find(" ");
        int count;
        std::from_chars(cube.begin(), cube.end(), count);
        auto color = cube.substr(pos + 1);

        if (color == "red") {
          m_red = count > m_red ? count : m_red;
        } else if (color == "green") {
          m_green = count > m_green ? count : m_green;
        } else {
          m_blue = count > m_blue ? count : m_blue;
        }
      }
    }
  }

  inline const int id() { return m_id; }
  inline const int red() { return m_red; }
  inline const int green() { return m_green; }
  inline const int blue() { return m_blue; }

 private:
  void strToVec(const std::string_view str, const std::string_view& delimiter,
                std::vector<std::string_view>& vec) {
    size_t begin = 0, end = 0;
    while ((end = str.find(delimiter, begin)) != std::string::npos) {
      vec.push_back(str.substr(begin, end - begin));
      begin = end + delimiter.size();
    }
    vec.push_back(str.substr(begin));
  }

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
  int sum = 0;
  while (std::getline(infile, line)) {
    auto game = Game(line);
    sum += game.red() * game.green() * game.blue();
  }
  std::cout << "The sum of the power of the sets is : " << sum << "\n";
  return 0;
}