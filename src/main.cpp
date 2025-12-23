#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <iostream>

#include "config.h"
#include "format.h"
#include "json.h"
#include "scanner.h"
#include "tree.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  Config config = parse_arguments(argc, argv);

  std::error_code ec;
  if (!fs::exists(config.targetPath, ec) ||
      !fs::is_directory(config.targetPath, ec)) {
    std::cerr << "Invalid directory: " << config.targetPath << "\n";
    return 1;
  }

  auto report = scan_directory_breakdown(config.targetPath);
  if (config.json) {
    std::cout << to_json(report) << "\n";
    return 0;
  }

  if (config.tree) {
    auto root = scan_directory_breakdown(config.targetPath);

    std::vector<bool> rootStack;
    for (std::size_t i = 0; i < root.entries.size(); ++i) {
      bool isLast = (i + 1 == root.entries.size());
      rootStack.clear();
      rootStack.push_back(isLast);
      print_tree(root.entries[i].path, rootStack, config.maxDepth,
                 root.totalSize);
    }
    return 0;
  }

  report.entries.erase(std::remove_if(report.entries.begin(),
                                      report.entries.end(),
                                      [&](const EntrySize &e) {
                                        return e.size < config.minSizeBytes;
                                      }),
                       report.entries.end());

  std::size_t limit = (config.topN == 0 || config.topN > report.entries.size())
                          ? report.entries.size()
                          : config.topN;

  constexpr int sizeColumnWidth = 12;

  for (std::size_t i = 0; i < limit; ++i) {
    const auto &entry = report.entries[i];

    std::cout << std::setw(sizeColumnWidth) << format_size(entry.size) << "  "
              << std::fixed << std::setprecision(2) << std::setw(6)
              << entry.percent << "%  " << format_bar(entry.percent) << "  "
              << entry.path.filename().string() << "\n";
  }

  if (report.skipped > 0) {
    std::cout << "\nSkipped entries due to errors: " << report.skipped << "\n";
  }

  return 0;
}
