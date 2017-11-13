// Q4STest.cpp : Defines the entry point for the console application.
//
#include "gtest/gtest.h"

TEST(setup_test_case, testWillPass)
{
 EXPECT_EQ(42, 42);
}