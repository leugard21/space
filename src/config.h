#pragma once

#include <cstddef>
#include <filesystem>

struct Config {
  std::filesystem::path targetPath;
  std::size_t topN;
  std::size_t depth;
  std::uintmax_t minSizeBytes;
  bool json;
};

Config parse_arguments(int argc, char *argv[]);
