#include "config.h"

#include <string>

namespace fs = std::filesystem;

static std::uintmax_t parse_size(const std::string &s) {
  if (s.empty())
    return 0;

  char unit = s.back();
  std::uintmax_t value = std::stoull(s);

  switch (unit) {
  case 'G':
  case 'g':
    return value * 1024ULL * 1024ULL * 1024ULL;
  case 'M':
  case 'm':
    return value * 1024ULL * 1024ULL;
  case 'K':
  case 'k':
    return value * 1024ULL;
  case 'B':
  case 'b':
    return value;
  default:
    return value;
  }
}

Config parse_arguments(int argc, char *argv[]) {
  Config config;
  config.targetPath = fs::current_path();
  config.topN = 0;
  config.depth = 1;
  config.minSizeBytes = 0;
  config.json = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--top" && i + 1 < argc) {
      config.topN = static_cast<std::size_t>(std::stoul(argv[++i]));
    } else if (arg == "--depth" && i + 1 < argc) {
      config.depth = static_cast<std::size_t>(std::stoul(argv[++i]));
    } else if (arg == "--min-size" && i + 1 < argc) {
      config.minSizeBytes = parse_size(argv[++i]);
    } else if (arg == "--json") {
      config.json = true;
    } else {
      config.targetPath = fs::path(arg);
    }
  }

  return config;
}
