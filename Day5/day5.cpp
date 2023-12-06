#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#include "commonFn.hpp"

void traverse_maps(std::istream& in, std::vector<long>& positions,
                   std::vector<std::pair<long, long>>& pos_ranges) {
  std::string line;
  std::vector<long> mapped{positions};
  std::vector<std::pair<long, long>> mapped_ranges;
  long dest_start, src_start, src_length;
  while (std::getline(in, line)) {
    if (line == "") {
      positions = mapped;
      for (auto& range : pos_ranges) {
        if (range.first > -1) mapped_ranges.push_back(range);
      }
      pos_ranges = mapped_ranges;
      mapped_ranges.clear();
    } else if (std::isdigit(line[0])) {
      std::stringstream ss{line};
      ss >> dest_start >> src_start >> src_length;
      long src_end = src_start + src_length;
      long offset = dest_start - src_start;

      // part 1 with single seeds
      for (int i = 0; i < positions.size(); ++i) {
        if (positions[i] >= src_start && positions[i] < src_end) {
          mapped[i] += offset;
        }
      }
      // part2 with ranges
      for (int i = 0; i < pos_ranges.size(); ++i) {
        long start = pos_ranges[i].first;
        long end = start + pos_ranges[i].second;
        auto intersect_start = std::max(start, src_start);
        auto intersect_end = std::min(end, src_end);
        auto length = intersect_end - intersect_start;
        if (start != -1 && length > 0) {
          mapped_ranges.push_back({intersect_start + offset, length});
          pos_ranges[i] = {-1, 0};
          if ((length = intersect_start - start) > 0) {
            pos_ranges.push_back({start, length});
          }
          if ((length = end - intersect_end) > 0) {
            pos_ranges.push_back({src_end, length});
          }
        }
      }
    }
  }
  positions = mapped;
  for (auto& range : pos_ranges) {
    if (range.first > -1) mapped_ranges.push_back(range);
  }
  pos_ranges = mapped_ranges;
}

int main(int argc, char* argv[]) {
  std::filesystem::path path{"./Day5/input"};
  std::string line;
  long location2 = std::numeric_limits<long>::max();

  if (argc == 2) {
    path = std::filesystem::path(argv[1]);
  }

  if (!std::filesystem::exists(path)) {
    std::cerr << "File not found: " << path << std::endl;
    return 1;
  }

  std::ifstream infile{path};
  std::getline(infile, line);
  std::vector<long> seeds;
  std::vector<std::pair<long, long>> seed_ranges;

  forEachNumber<long>(line, [&seeds](long n) { seeds.push_back(n); });
  for (int i = 0; i < seeds.size(); i += 2) {
    seed_ranges.push_back({seeds[i], seeds[i + 1]});
  }
  std::getline(infile, line);

  traverse_maps(infile, seeds, seed_ranges);

  long location1 = std::ranges::min(seeds);

  for (auto& location : seed_ranges) {
    if (location.first < location2) {
      location2 = location.first;
    }
  }

  std::cout << std::format("1: The lowest location number {}\n", location1);
  std::cout << std::format("2: The lowest location number {}\n", location2);

  return 0;
}
