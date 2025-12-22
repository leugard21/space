#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

struct EntrySize {
  std::filesystem::path path;
  std::uintmax_t size;
  double percent;
};

struct ScanReport {
  std::vector<EntrySize> entries;
  std::size_t skipped;
  std::uintmax_t totalSize;
};

ScanReport scan_directory_breakdown(const std::filesystem::path &path,
                                    std::size_t depth);
