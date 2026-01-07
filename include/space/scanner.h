#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

struct EntrySize {
  std::filesystem::path path;
  std::uintmax_t size;
  double percent;
  bool isDir;
};

struct ScanReport {
  std::vector<EntrySize> entries;
  std::size_t skipped;
  std::uintmax_t totalSize;
};

std::uintmax_t safe_directory_size(const fs::path &path, std::size_t &skipped);

ScanReport scan_directory_breakdown(const std::filesystem::path &path);
