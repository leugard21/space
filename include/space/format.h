#pragma once

#include <cstdint>
#include <string>

std::string format_size(std::uintmax_t bytes);
std::string format_bar(double percent, std::size_t width = 30);
std::string colorize_path(const std::string &path, bool isDir,
                          std::uintmax_t size, bool enabled);
