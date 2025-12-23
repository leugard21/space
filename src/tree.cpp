#include "tree.h"
#include "cache.h"
#include "format.h"
#include "scanner.h"

#include <algorithm>
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

static std::uintmax_t get_cached_size(const fs::path &path, SizeCache &cache,
                                      std::size_t &skipped) {
  auto it = cache.map.find(path);
  if (it != cache.map.end()) {
    return it->second;
  }

  std::uintmax_t size = 0;
  std::error_code ec;

  if (fs::is_directory(path, ec)) {
    size = safe_directory_size(path, skipped);
  } else {
    size = fs::file_size(path, ec);
    if (ec) {
      size = 0;
      ++skipped;
    }
  }

  cache.map.emplace(path, size);
  return size;
}

void print_tree(const fs::path &path, const std::vector<bool> &lastStack,
                std::size_t maxDepth, std::uintmax_t rootSize,
                std::uintmax_t minSizeBytes, SizeCache &cache) {
  std::size_t depth = lastStack.size();
  if (maxDepth != static_cast<std::size_t>(-1) && depth > maxDepth) {
    return;
  }

  std::size_t skipped = 0;
  std::uintmax_t size = get_cached_size(path, cache, skipped);

  if (size < minSizeBytes) {
    return;
  }

  print_prefix(lastStack);
  std::cout << format_size(size) << "  " << path.filename().string() << "\n";

  std::error_code ec;
  if (!fs::is_directory(path, ec) || ec) {
    return;
  }

  std::vector<fs::directory_entry> children;
  for (const auto &e : fs::directory_iterator(path, ec)) {
    if (!ec) {
      children.push_back(e);
    }
  }

  std::sort(children.begin(), children.end(),
            [&](const fs::directory_entry &a, const fs::directory_entry &b) {
              std::size_t s = 0;
              auto sa = get_cached_size(a.path(), cache, s);
              auto sb = get_cached_size(b.path(), cache, s);
              if (sa != sb)
                return sa > sb;
              return a.path().filename() < b.path().filename();
            });

  for (std::size_t i = 0; i < children.size(); ++i) {
    bool isLast = (i + 1 == children.size());
    auto nextStack = lastStack;
    nextStack.push_back(isLast);

    print_tree(children[i].path(), nextStack, maxDepth, rootSize, minSizeBytes,
               cache);
  }
}
