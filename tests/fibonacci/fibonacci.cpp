#include <gtest/gtest.h>

#include <vector>

#include <fibonacci.hpp>

namespace {
class FibonacciFixtureTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace

TEST_F(FibonacciFixtureTest, Sequence) {
  std::vector<std::size_t> solution{0, 1, 1, 2, 3, 5, 8};
  auto res = tasks::fibonacci::Fibonacci(solution.size());

  ASSERT_EQ(res, solution);

  solution = std::vector<std::size_t>{
      0,   1,   1,   2,   3,   5,    8,    13,   21,   34,    55,   89,
      144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711};
  res = tasks::fibonacci::Fibonacci(solution.size());
  ASSERT_EQ(res, solution);

  ASSERT_TRUE(tasks::fibonacci::Fibonacci(0).empty());

  solution = std::vector<std::size_t>{0};
  res = tasks::fibonacci::Fibonacci(solution.size());
  ASSERT_EQ(res, solution);
}