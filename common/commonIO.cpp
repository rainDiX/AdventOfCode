#include "commonIO.hpp"

#include <cstdio>
#include <fstream>

std::expected<std::string, io_errc> readFile(std::filesystem::path& path) {
  std::string str;
  std::string error;
  if (!std::filesystem::exists(path)) {
    return std::unexpected{io_errc::file_not_found};
  }
  std::ifstream in(path);
  if (in) {
    std::string buffer;
    in.seekg(0, std::ios::end);
    buffer.resize(in.tellg());
    in.seekg(0);
    in.read(&buffer[0], buffer.size());
    in.close();
    return (buffer);
  }
  return std::unexpected{io_errc::failed_to_read_file};
}

std::expected<std::string, int> readFileC(std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    return std::unexpected{ ENOENT };
  }
  std::FILE* fp = std::fopen(path.c_str(), "rb");
  if (fp) {
    std::string buffer;
    std::fseek(fp, 0, SEEK_END);
    buffer.resize(std::ftell(fp));
    std::rewind(fp);
    std::fread(&buffer[0], 1, buffer.size(), fp);
    std::fclose(fp);
    return (buffer);
  }
  return std::unexpected{ errno };
}
