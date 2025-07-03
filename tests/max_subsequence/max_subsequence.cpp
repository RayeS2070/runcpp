#include <gtest/gtest.h>

#include <vector>

#include <max_subsequence.hpp>

namespace {
class DynProgFixtureTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace

TEST_F(DynProgFixtureTest, MaxSubSeqSum) {
  std::vector data{-2, -3, 2, 4, 7, -8, -9, -10, 3, 8, 4, -2, 8, 6, -40, 1};
  constexpr auto solution = 3 + 8 + 4 - 2 + 8 + 6;
  
  auto res = tasks::dp::GetMaxSubseqValue(data);

  ASSERT_EQ(res, 27);
}