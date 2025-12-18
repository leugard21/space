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

  auto breakdown = scan_directory_breakdown(targetPath);

  for (const auto &entry : breakdown) {
    std::cout << format_size(entry.size) << "\t"
              << entry.path.filename().string() << "\n";
  }

  return 0;
}
