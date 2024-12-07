#include <algorithm>
#include <any>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <format>
#include <functional>
#include <future>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <ranges>
#include <span>
#include <sstream>
#include <stack>
#include <stacktrace>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include <boost/locale.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/util.hpp>

#include <boost/stacktrace.hpp>
#include <boost/stacktrace/stacktrace.hpp>
#include <boost/stacktrace/this_thread.hpp>

#include <fmt/base.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

std::vector<int> CountSort(std::vector<int> data) {
  std::vector<std::pair<int, std::size_t>> sort_helper;

  std::ranges::sort(data);

  for (auto&& e : data) {
    if (sort_helper.empty() || sort_helper.back().first != e)
      sort_helper.emplace_back(e, 1);
    else
      sort_helper.back().second++;
  }

  std::ranges::sort(sort_helper, [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  std::vector<int> result;
  for (auto&& [k, v] : sort_helper)
    std::fill_n(std::back_inserter(result), v, k);

  // for (auto&& _ : std::views::iota(0ul, v)) result.push_back(k);

  return result;
}

auto main(int, char*[]) -> int {
  fmt::println("{}", fmt::join(CountSort({1, 1, 1}), ", "));
  fmt::println("{}", fmt::join(CountSort({1}), ", "));
  fmt::println("{}", fmt::join(CountSort({1, 1, 2, 3, 3, 3}), ", "));
  fmt::println("{}", fmt::join(CountSort({1, 1, 2, 2, 3, 3}), ", "));

  return 0;
}
