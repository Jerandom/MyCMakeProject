// _Test.cpp : Defines the entry point for the application.
//

#include <gtest/gtest.h>

using namespace std;

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

int main()
{
    // Run google test
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
 
    return 0;
}
