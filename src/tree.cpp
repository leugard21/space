#include "tree.h"
#include "format.h"
#include "scanner.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

static void print_prefix(const std::vector<bool> &lastStack) {
  for (std::size_t i = 0; i + 1 < lastStack.size(); ++i) {
    std::cout << (lastStack[i] ? "    " : "│   ");
  }

  if (!lastStack.empty()) {
    std::cout << (lastStack.back() ? "└── " : "├── ");
  }
}

void print_tree(const fs::path &path, const std::vector<bool> &lastStack,
                std::size_t maxDepth, std::uintmax_t rootSize) {
  std::size_t depth = lastStack.size();
  if (maxDepth != static_cast<std::size_t>(-1) && depth > maxDepth) {
    return;
  }

  std::size_t skipped = 0;
  std::uintmax_t size = 0;

  if (fs::is_directory(path)) {
    size = scan_directory_breakdown(path).totalSize;
  } else {
    std::error_code ec;
    size = fs::file_size(path, ec);
    if (ec)
      size = 0;
  }

  double percent = rootSize > 0 ? static_cast<double>(size) * 100.0 /
                                      static_cast<double>(rootSize)
                                : 0.0;

  print_prefix(lastStack);
  std::cout << format_size(size) << "  " << path.filename().string() << "\n";

  if (!fs::is_directory(path)) {
    return;
  }

  std::vector<fs::directory_entry> children;
  for (const auto &e : fs::directory_iterator(path)) {
    children.push_back(e);
  }

  for (std::size_t i = 0; i < children.size(); ++i) {
    bool isLast = (i + 1 == children.size());
    auto nextStack = lastStack;
    nextStack.push_back(isLast);
    print_tree(children[i].path(), nextStack, maxDepth, rootSize);
  }
}
