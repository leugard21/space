#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

struct EntrySize {
  std::filesystem::path path;
  std::uintmax_t size;
};

std::uintmax_t calculate_directory_size(const std::filesystem::path &path);
std::vector<EntrySize>
scan_directory_breakdown(const std::filesystem::path &path);
