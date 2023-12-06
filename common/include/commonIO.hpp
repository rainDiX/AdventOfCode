#pragma once
#include <expected>
#include <filesystem>
#include <string>

enum class io_errc {
  file_not_found,
  failed_to_open_file,
  failed_to_read_file,
  failed_to_write_file,
};

std::expected<std::string, io_errc> readFile(std::filesystem::path& path);

std::expected<std::string, int> readFileC(std::filesystem::path& path);
