#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>

struct Config {
  std::filesystem::path targetPath;
  std::size_t topN;
  std::uintmax_t minSizeBytes;
  bool json;
  bool tree;
  std::size_t maxDepth;
};

Config parse_arguments(int argc, char *argv[]);
