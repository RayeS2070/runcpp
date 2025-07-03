#pragma once

#include <cstddef>
#include <string_view>
#include <utility>

namespace tasks::manacher {
std::string Manacher(std::string_view data) noexcept;
}