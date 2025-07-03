#include <manacher.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace {

std::pair<std::size_t, std::size_t> Manacher(std::string_view s) {
  std::vector<std::int32_t> palindrome_radii(s.size(), 0);

  int center{0};
  int radius{0};

  for (; center < s.size();) {
    for (auto l = center - (radius + 1), r = center + (radius + 1);
         l >= 0 && r < static_cast<int>(s.size()) && s[l] == s[r]; ++radius, --l, ++r);

    palindrome_radii[center] = radius;

    auto old_center = center;
    auto old_radius = radius;

    ++center;
    radius = 0;

    while (center <= old_center + old_radius) {
      auto mirrored_center = old_center - (center - old_center);
      auto max_mirrored_radius = old_center + old_radius - center;

      if (palindrome_radii[mirrored_center] < max_mirrored_radius) {
        palindrome_radii[center] = palindrome_radii[mirrored_center];
        ++center;
      } else if (palindrome_radii[mirrored_center] > max_mirrored_radius) {
        palindrome_radii[center] = max_mirrored_radius;
        ++center;
      } else {
        radius = max_mirrored_radius;
        break;
      }
    }
  }

  auto max_element = std::ranges::max_element(palindrome_radii);
  if (max_element == palindrome_radii.end()) return {0, 0};

  auto pos = std::distance(palindrome_radii.begin(), max_element);
  pos -= *max_element;
  return {pos, *max_element};
}

}  // namespace

namespace tasks::manacher {
std::string Manacher(std::string_view data) noexcept {
  std::string s("#");
  std::ranges::for_each(data, [&s](const char c) {
    s += c;
    s += "#";
  });

  auto [pos, size] = ::Manacher(s);
  pos /= 2;
  return std::string(data.data() + pos, size);
}
}  // namespace tasks::manacher