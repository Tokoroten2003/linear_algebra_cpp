/**
 * @file alias.hpp
 * @brief declare aliases
 */
#pragma once

#include <vector>

namespace mcalc {
/**
 * @brief alias of std::vector
 *
 * @tparam T
 */
template <typename T> using V1 = typename std::vector<T>;

/**
 * @brief alias of std::vector<std::vector> (2 dimentional list)
 *
 * @tparam T
 */
template <typename T> using V2 = typename std::vector<std::vector<T>>;
} // namespace mcalc
