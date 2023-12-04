#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string_view>
#include <vector>

#include "commonFn.hpp"

struct Card {
  int id;
  int points;
  int win_count;
  std::vector<int> winning;
};

void parseCard(const std::string_view cardStr, Card& card) {
  // cut the card id:
  auto pos = cardStr.find(":");
  auto idStr = cardStr.substr(0, pos);
  auto numbersStr = cardStr.substr(pos + 1);
  std::from_chars(idStr.begin() + 5, idStr.end(), card.id);

  pos = numbersStr.find(" | ");
  auto winStr = numbersStr.substr(0, pos);
  auto rollStr = numbersStr.substr(pos + 3);

  card.winning.clear();
  forEachNumber(winStr, [&card](int n) { card.winning.push_back(n); });

  card.points = 0;
  card.win_count = 0;
  auto calculateScore = [&card](int n) {
    if (std::find(card.winning.begin(), card.winning.end(), n) != card.winning.end()) {
      card.points = card.points > 0 ? card.points * 2 : 1;
      card.win_count += 1;
    }
  };
  forEachNumber(rollStr, calculateScore);
}

int cardCount(std::vector<int>& wins) {
  std::vector<int> card_counts(wins.size(), 1);
  for (int i = 0; i < wins.size(); ++i) {
    int dupe = card_counts[i];
    for (int j = i + 1; j <= i + wins[i]; ++j) {
      card_counts[j] += dupe;
    }
  }
  return std::accumulate(card_counts.begin(), card_counts.end(), 0);
}

int main(int argc, char* argv[]) {
  std::filesystem::path path{"./Day4/input"};

  if (argc == 2) {
    path = std::filesystem::path(argv[1]);
  }

  if (!std::filesystem::exists(path)) {
    std::cerr << "File not found: " << path << std::endl;
    return 1;
  }

  std::ifstream infile{path};
  std::string line;
  Card card;
  std::vector<int> wins;
  wins.reserve(250);
  int sum_part1 = 0, part2 = 0;
  while (std::getline(infile, line)) {
    parseCard(line, card);
    sum_part1 += card.points;
    wins.push_back(card.win_count);
  }
  part2 = cardCount(wins);
  std::cout << "1: The total of points is : " << sum_part1 << "\n";
  std::cout << "2: The total of scatchcard is : " << part2 << "\n";
  return 0;
}