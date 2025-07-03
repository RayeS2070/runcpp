#pragma once

#include <string>

namespace tasks::skl {
class SmallestKLength {
 public:
  SmallestKLength();
  ~SmallestKLength();

  std::string Resolve(std::string s, int k, char letter, int rep);
private:
};
}  // namespace tasks::skl
