#include "scanner.h"

#include <algorithm>

namespace fs = std::filesystem;

std::uintmax_t calculate_directory_size(const std::filesystem::path &path) {
  std::uintmax_t totalSize = 0;
  std::error_code ec;

  for (auto it = fs::recursive_directory_iterator(
           path, fs::directory_options::skip_permission_denied, ec);
       it != fs::recursive_directory_iterator(); ++it) {
    if (it->is_regular_file(ec)) {
      totalSize += it->file_size(ec);
    }
  }

  return totalSize;
}

std::vector<EntrySize>
scan_directory_breakdown(const std::filesystem::path &path) {
  std::vector<EntrySize> results;
  std::error_code ec;

  for (const auto &entry : fs::directory_iterator(path, ec)) {
    EntrySize item;
    item.path = entry.path();

    if (entry.is_directory(ec)) {
      item.size = calculate_directory_size(entry.path());
    } else if (entry.is_regular_file(ec)) {
      item.size = entry.file_size(ec);
    } else {
      continue;
    }

    results.push_back(item);
  }

  std::sort(
      results.begin(), results.end(),
      [](const EntrySize &a, const EntrySize &b) { return a.size > b.size; });

  return results;
}
