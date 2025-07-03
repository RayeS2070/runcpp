#include <max_subsequence.hpp>

#include <span>

namespace tasks::dp {

int GetMaxSubseqValue(const std::vector<int>& data) {
  std::vector<int> line(data.size() * data.size(), 0);
  std::vector<std::span<int>> dm(data.size());
  for (auto i = 0ull; i < data.size(); ++i)
    dm[i] = std::span(line.data() + i * data.size(), data.size());

  for (auto i = 0ull; i < data.size(); ++i) dm[i][i] = data[i];

  int result{data.front()};

  for (auto i = 0ull; i < data.size(); ++i)
    for (auto j = i + 1u; j < data.size(); ++j) {
      result = std::max(dm[i][j] = dm[i][j - 1u] + dm[j][j], result);
    }

  return result;
}

}  // namespace tasks::dp
