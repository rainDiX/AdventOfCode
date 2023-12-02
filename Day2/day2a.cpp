#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define RED 12
#define GREEN 13
#define BLUE 14

class Game {
 public:
  Game(const std::string& gameStr) {
    const std::string colors[] = {"red", "green", "blue"};
    m_red = 0, m_green = 0, m_blue = 0;

    // cut the game id:
    auto pos = gameStr.find(": ");
    auto idStr = gameStr.substr(0, pos);
    auto setsStr = gameStr.substr(pos + 2);
    m_id = std::stoi(idStr.substr(5));

    auto sets = std::vector<std::string>();
    strToVec(setsStr, "; ", sets);

    for (auto& setStr : sets) {
      auto cubes = std::vector<std::string>();
      strToVec(setStr, ", ", cubes);

      for (auto& cube : cubes) {
        pos = cube.find(" ");
        int count = std::stoi(cube.substr(0, pos));
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

  inline const bool isPossible() {
    return !(m_red > RED || m_green > GREEN || m_blue > BLUE);
  }

  inline const int id() { return m_id; }

 private:
  void strToVec(const std::string& str, const std::string& delimiter,
                std::vector<std::string>& vec) {
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
    if (game.isPossible()) {
      sum += game.id();
    }
  }
  std::cout << "the sum of the IDs of the possible games is : " << sum << "\n";
  return 0;
}