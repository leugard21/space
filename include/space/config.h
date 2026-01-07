#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>

struct Config {
  std::filesystem::path targetPath;
  std::size_t topN;
  std::uintmax_t minSizeBytes;
  bool json;
  bool tree;
  std::size_t maxDepth;
  bool showVersion;
  bool color;
  std::string sortOrder;
};

Config parse_arguments(int argc, char *argv[]);
