#include <iostream>

#include "format.h"
#include "scanner.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  fs::path targetPath = (argc == 2) ? fs::path(argv[1]) : fs::current_path();

  std::error_code ec;
  if (!fs::exists(targetPath, ec) || !fs::is_directory(targetPath, ec)) {
    std::cerr << "Invalid directory: " << targetPath << "\n";
    return 1;
  }

  auto report = scan_directory_breakdown(targetPath);

  constexpr int sizeColumnWidth = 12;

  for (const auto &entry : report.entries) {
    std::cout << std::setw(sizeColumnWidth) << format_size(entry.size) << "  "
              << entry.path.filename().string() << "\n";
  }

  if (report.skipped > 0) {
    std::cout << "\nSkipped entries due to errors: " << report.skipped << "\n";
  }

  return 0;
}
