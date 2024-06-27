// _Test.cpp : Defines the entry point for the application.
//

#include "QRGenerator/QrCodeManager.h"

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(TestCaseName, TestName) 
{
    vector<int> vec = { 1,2,3,4,5 };
    EXPECT_EQ(3, 3);
    EXPECT_TRUE(true);
}

int main()
{
    // Run google test
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
 
    return 0;
}
