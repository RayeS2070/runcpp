#include <fibonacci.hpp>

#include <algorithm>
#include <generator>
#include <utility>
#include <vector>

namespace tasks::fibonacci {

#if __cpp_lib_generator == 202207L
namespace {
std::generator<std::size_t> GetNextFibonacci(std::size_t n) {
  std::size_t a{0};
  std::size_t b{1};

  for (std::size_t count{0u}; count < n; ++count) {
    co_yield a;
    a = std::exchange(b, a + b);
  }
}

}  // namespace

std::vector<std::size_t> Fibonacci(std::size_t n) {
  std::vector<std::size_t> result;
  std::ranges::copy(GetNextFibonacci(n), std::back_inserter(result));

  return result;
}

#else

namespace {}

std::vector<std::size_t> Fibonacci(std::size_t n) {
  std::vector<std::size_t> result;
  std::generate_n(std::back_inserter(result), n,
                  [a = 0ull, b = 1ull]() mutable constexpr {
                    auto res = a;
                    a = std::exchange(b, a + b);
                    return res;
                  });

  return result;
}

#endif
}  // namespace tasks::fibonacci
