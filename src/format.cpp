#include "format.h"

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
