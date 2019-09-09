#include <gtest/gtest.h>

extern int add(int a, int b);

TEST(testCase, test0)
{
    EXPECT_EQ(add(2, 3), 5);
}

TEST(testCase, test1)
{
    EXPECT_EQ(add(-1, 3), 2);
}

TEST(testCase, test2)
{
    EXPECT_EQ(add(0, 0), 0);
}
