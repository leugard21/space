#pragma once

#include <filesystem>
#include <vector>

void print_tree(const std::filesystem::path &path,
                const std::vector<bool> &lastStack, std::size_t maxDepth,
                std::uintmax_t rootSize);
