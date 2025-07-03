#include <gtest/gtest.h>

#include <vector>

#include <smallest_k_length.hpp>

namespace {
class SmallersKLenFixtureTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace

TEST_F(SmallersKLenFixtureTest, MaxSubSeqSum) {
  tasks::skl::SmallestKLength resolver;

  ASSERT_EQ(resolver.Resolve("leetcode", 4, 'e', 2), "ecde");
  ASSERT_EQ(resolver.Resolve("aaabbbcccddd", 3, 'b', 2), "abb");
  ASSERT_EQ(resolver.Resolve("adffhjfmmmmorsfff", 6, 'f', 5), "afffff");
  ASSERT_EQ(resolver.Resolve("mmmxmxymmm", 8, 'm', 4), "mmmmxmmm");
}