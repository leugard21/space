#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

struct EntrySize {
  std::filesystem::path path;
  std::uintmax_t size;
};

struct ScanReport {
  std::vector<EntrySize> entries;
  std::size_t skipped;
};

ScanReport scan_directory_breakdown(const std::filesystem::path &path);
