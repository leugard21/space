#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <vector>

struct SizeCache;

void print_tree(const std::filesystem::path &path,
                const std::vector<bool> &lastStack, std::size_t maxDepth,
                std::uintmax_t rootSize, std::uintmax_t minSizeBytes,
                SizeCache &cache);
