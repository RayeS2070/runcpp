#include <benchmark/benchmark.h>
#include <benchmark/export.h>

#include <algorithm>
#include <concepts>
#include <ranges>

namespace {
using namespace std::string_view_literals;
constexpr auto kDelim = ' ';
constexpr auto kMinSize = 50UZ;
constexpr auto kMaxSize = 1000UZ;
constexpr auto kFrom = 32;
constexpr auto kTo = 127;
constexpr auto kCharCount = 250000UZ;

auto Processing(std::string_view data) { benchmark::DoNotOptimize(data); }

auto GenerateString(std::int64_t lower_bound = kFrom,
                    std::int64_t upper_bound = kTo) {
  static const auto str = std::ranges::to<std::string>(
      benchmark::CreateRange(lower_bound, upper_bound, kCharCount));
  return str;
}

void DummyRangeImpl(benchmark::State& state) {
  auto data = GenerateString();

  for (auto _ : state) {
    auto range = data | std::views::split(kDelim) |
                 std::views::filter([](std::ranges::range auto rng) {
                   return rng.size() >= kMinSize;
                 }) |
                 std::views::filter([](std::ranges::range auto rng) {
                   return rng.size() < kMaxSize;
                 }) |
                 std::views::transform([](auto rng) {
                   return rng | std::views::transform([](char c) {
                            if (c >= '0' && c <= '9') {
                              return '!';
                            }
                            return c;
                          });
                 });

    for (auto v : range) {
      std::string result{v.begin(), v.end()};
      Processing(result);
    }
  }
}
BENCHMARK(DummyRangeImpl);

struct word_sentinel {
  bool operator==(char const* p) const { return *p == '\0' || *p == ' '; }
};

struct word : std::ranges::view_interface<word> {
  char const* p = nullptr;
  word() = default;
  word(char const* p) : p(p) {}
  auto begin() const { return p; }
  auto end() const { return word_sentinel{}; }
  auto size() const {
    return static_cast<std::size_t>(std::ranges::distance(begin(), end()));
  }
};

void RangeImpl(benchmark::State& state) {
  auto data = GenerateString();

  for (auto _ : state) {
    auto range = data | std::views::lazy_split(kDelim) |
                 std::views::filter([](auto rng) {
                   auto size = std::ranges::distance(rng.begin(), rng.end());
                   return size >= kMinSize && size < kMaxSize;
                 }) |
                 std::views::transform([](auto rng) {
                   return rng | std::views::transform([](char c) {
                            if (c >= '0' && c <= '9') {
                              return '!';
                            }
                            return c;
                          });
                 });

    for (auto v : range) {
      std::string result;
      for (auto i : v) result += i;
      Processing(result);
    }
  }
}
BENCHMARK(RangeImpl);

void BasicAlgoImpl(benchmark::State& state) {
  auto data = GenerateString();

  for (auto _ : state) {
    auto prev_iter = data.begin();
    for (auto current_iter =
             std::find(std::next(prev_iter), data.end(), kDelim);
         current_iter != data.end();
         prev_iter = current_iter, current_iter = find(std::next(current_iter),
                                                       data.end(), kDelim)) {
      auto range = std::ranges::subrange(prev_iter, current_iter);
      if (auto size = range.size(); size < kMinSize || size >= kMaxSize)
        continue;

      std::string result(prev_iter, current_iter);
      std::transform(result.begin(), result.end(), result.begin(), [](char c) {
        if (c >= '0' && c <= '9') {
          return '!';
        }
        return c;
      });
      Processing(result);
    }
  }
}
BENCHMARK(BasicAlgoImpl);

void SimpleRange(benchmark::State& state) {
  auto data = GenerateString();
  for (auto _ : state) {
    std::string result{data.begin(), data.end()};
    std::ranges::transform(result, result.begin(), [](char c) {
      if (c >= '0' && c <= '9') {
        return '!';
      }
      return c;
    });
    std::ranges::sort(result, std::greater<>{});
    Processing(result);
  }
}
BENCHMARK(SimpleRange);

void SimpleAlgo(benchmark::State& state) {
  auto data = GenerateString();
  for (auto _ : state) {
    std::string result{data.begin(), data.end()};
    std::transform(result.begin(), result.end(), result.begin(), [](char c) {
      if (c >= '0' && c <= '9') {
        return '!';
      }
      return c;
    });
    std::sort(result.begin(), result.end(), std::greater<>{});
    Processing(result);
  }
}
BENCHMARK(SimpleAlgo);
}  // namespace

BENCHMARK_MAIN();