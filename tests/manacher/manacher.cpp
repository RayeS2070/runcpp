#include <gtest/gtest.h>

#include <vector>

#include <manacher.hpp>

namespace {
class ManacherFixtureTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace

TEST_F(ManacherFixtureTest, Sequence) {
  using ::tasks::manacher::Manacher;
  ASSERT_EQ(Manacher("babad"), "bab");
  ASSERT_EQ(Manacher("cbbd"), "bb");
  ASSERT_EQ(Manacher("a"), "a");
}