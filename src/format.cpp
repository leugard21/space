#include "space/format.h"

#include <iomanip>
#include <iostream>
#include <sstream>

std::string format_size(std::uintmax_t bytes) {
  constexpr const char *units[] = {"B", "KB", "MB", "GB", "TB"};
  double size = static_cast<double>(bytes);
  std::size_t unit = 0;

  while (size >= 1024.0 && unit < 4) {
    size /= 1024.0;
    ++unit;
  }

  std::ostringstream out;
  if (unit == 0) {
    out << static_cast<std::uintmax_t>(size) << " " << units[unit];
  } else {
    out << std::fixed << std::setprecision(2) << size << " " << units[unit];
  }

  return out.str();
}

std::string format_bar(double percent, std::size_t width) {
  std::size_t filled = static_cast<std::size_t>((percent / 100.0) * width);
  if (filled > width)
    filled = width;

  return std::string(filled, '#') + std::string(width - filled, '.');
}

std::string colorize_path(const std::string &path, bool isDir,
                          std::uintmax_t size, bool enabled) {
  if (!enabled)
    return path;

  // Colors
  const char *RESET = "\033[0m";
  const char *BLUE = "\033[1;34m";   // Bold Blue for directories
  const char *RED = "\033[1;31m";    // Bold Red for > 1GB
  const char *YELLOW = "\033[1;33m"; // Bold Yellow for > 100MB
  const char *GREEN = "\033[1;32m";  // Bold Green for others

  std::string color = GREEN;

  if (isDir) {
    color = BLUE;
  } else {
    if (size > 1024ULL * 1024ULL * 1024ULL) {
      color = RED;
    } else if (size > 100ULL * 1024ULL * 1024ULL) {
      color = YELLOW;
    }
  }

  return std::string(color) + path + RESET;
}
