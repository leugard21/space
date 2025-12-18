#pragma once

#include <cstddef>
#include <filesystem>

struct Config {
  std::filesystem::path targetPath;
  std::size_t topN;
};

Config parse_arguments(int argc, char *argv[]);
