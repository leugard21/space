#include "config.h"

#include <string>

namespace fs = std::filesystem;

static std::uintmax_t parse_size(const std::string &s) {
  if (s.empty())
    return 0;
  char u = s.back();
  std::uintmax_t v = std::stoull(s);
  if (u == 'G' || u == 'g')
    return v * 1024ULL * 1024ULL * 1024ULL;
  if (u == 'M' || u == 'm')
    return v * 1024ULL * 1024ULL;
  if (u == 'K' || u == 'k')
    return v * 1024ULL;
  return v;
}

Config parse_arguments(int argc, char *argv[]) {
  Config c{};
  c.targetPath = fs::current_path();
  c.topN = 0;
  c.minSizeBytes = 0;
  c.json = false;
  c.tree = false;
  c.maxDepth = static_cast<std::size_t>(-1);

  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "--top" && i + 1 < argc)
      c.topN = std::stoull(argv[++i]);
    else if (a == "--min-size" && i + 1 < argc)
      c.minSizeBytes = parse_size(argv[++i]);
    else if (a == "--json")
      c.json = true;
    else if (a == "--tree")
      c.tree = true;
    else if (a == "--max-depth" && i + 1 < argc)
      c.maxDepth = std::stoull(argv[++i]);
    else
      c.targetPath = fs::path(a);
  }
  return c;
}
