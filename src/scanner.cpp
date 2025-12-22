#include "scanner.h"

#include <algorithm>

namespace fs = std::filesystem;

static std::uintmax_t safe_directory_size(const fs::path &path,
                                          std::size_t maxDepth,
                                          std::size_t &skipped) {
  std::uintmax_t total = 0;
  std::error_code ec;

  fs::recursive_directory_iterator it(
      path, fs::directory_options::skip_permission_denied, ec);

  for (; it != fs::recursive_directory_iterator(); ++it) {
    if (ec) {
      ++skipped;
      ec.clear();
      continue;
    }

    if (maxDepth > 0 && it.depth() >= static_cast<int>(maxDepth)) {
      it.disable_recursion_pending();
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

ScanReport scan_directory_breakdown(const fs::path &path, std::size_t depth) {
  ScanReport report{};
  std::error_code ec;

  if (depth == 0) {
    return report;
  }

  for (const auto &entry : fs::directory_iterator(path, ec)) {
    if (ec) {
      ++report.skipped;
      ec.clear();
      continue;
    }

    EntrySize item;
    item.path = entry.path();

    if (entry.is_directory(ec)) {
      item.size = safe_directory_size(entry.path(), depth - 1, report.skipped);
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
