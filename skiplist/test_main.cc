// This automatically runs all the googletest tests that it is linked
// with. Googly magic! The tests are in *_test.cc.

#include <gtest/gtest.h>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
