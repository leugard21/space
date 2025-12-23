#pragma once

#include <cstdint>
#include <filesystem>
#include <unordered_map>

struct SizeCache {
  std::unordered_map<std::filesystem::path, std::uintmax_t> map;
};
