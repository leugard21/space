#include "scanner.h"

#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

static std::uintmax_t safe_directory_size(const fs::path &path,
                                          std::size_t &skipped) {
  std::uintmax_t total = 0;
  std::error_code ec;

  for (auto it = fs::recursive_directory_iterator(
           path, fs::directory_options::skip_permission_denied, ec);
       it != fs::recursive_directory_iterator(); ++it) {

    if (ec) {
      ++skipped;
      ec.clear();
      continue;
    }

    if (it->is_regular_file(ec)) {
      total += it->file_size(ec);
      if (ec) {
        ++skipped;
        ec.clear();
      }
    }
  }

  return total;
}

ScanReport scan_directory_breakdown(const fs::path &path) {
  ScanReport report{};
  std::error_code ec;

  for (const auto &entry : fs::directory_iterator(path, ec)) {
    if (ec) {
      ++report.skipped;
      ec.clear();
      continue;
    }

    EntrySize item;
    item.path = entry.path();

    if (entry.is_directory(ec)) {
      item.size = safe_directory_size(entry.path(), report.skipped);
    } else if (entry.is_regular_file(ec)) {
      item.size = entry.file_size(ec);
      if (ec) {
        ++report.skipped;
        ec.clear();
        continue;
      }
    } else {
      continue;
    }

    report.totalSize += item.size;
    report.entries.push_back(item);
  }

  for (auto &entry : report.entries) {
    entry.percent = report.totalSize > 0
                        ? (static_cast<double>(entry.size) * 100.0 /
                           static_cast<double>(report.totalSize))
                        : 0.0;
  }

  std::sort(report.entries.begin(), report.entries.end(),
            [](const EntrySize &a, const EntrySize &b) {
              if (a.size != b.size) {
                return a.size > b.size;
              }
              return a.path.filename() < b.path.filename();
            });

  return report;
}
