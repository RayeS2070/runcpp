#include "smallest_k_length.hpp"

#include <algorithm>
#include <stack>
#include <vector>

namespace tasks::skl {
SmallestKLength::SmallestKLength() = default;

SmallestKLength::~SmallestKLength() = default;

std::string SmallestKLength::Resolve(std::string s, int k, char letter,
                                     int rep) {
  auto req = rep;
  auto num_letters = std::count(s.begin(), s.end(), letter);
  std::string result;

  for (auto it = s.begin(); it != s.end(); ++it) {
    const auto& c = *it;
    const auto i = std::distance(s.begin(),it);
    auto suffix_size = std::distance(it, s.end());

    while (!result.empty() && result.back() > c &&
           result.size() + suffix_size - 1 >= k &&
           (result.back() != letter || num_letters > req)) {
      const auto back = result.back();
      result.pop_back();
      if (back == letter) {
        ++req;
      }
    }

    if (result.size() < k) {
      if (c == letter) {
        result += c;
        --req;
      } else if (k > result.size() + req) {
        result += c;
      }
    }
    if (c == letter) {
      --num_letters;
    }
  }

  return result;
}

}  // namespace tasks::skl