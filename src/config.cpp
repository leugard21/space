#include "config.h"

#include <string>

namespace fs = std::filesystem;

Config parse_arguments(int argc, char *argv[]) {
  Config config;
  config.targetPath = fs::current_path();
  config.topN = 0;
  config.depth = 1;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--top" && i + 1 < argc) {
      config.topN = static_cast<std::size_t>(std::stoul(argv[++i]));
    } else if (arg == "--depth" && i + 1 < argc) {
      config.depth = static_cast<std::size_t>(std::stoul(argv[++i]));
    } else {
      config.targetPath = fs::path(arg);
    }
  }

  return config;
}
