#include <gtest/gtest.h>
#include "../src/funkcje.cpp"

TEST(MyFunctionTest, PositiveNumbers) {
    EXPECT_EQ(MyFunction(1, 2), 3);
}

TEST(MyFunctionTest, NegativeNumbers) {
    EXPECT_EQ(MyFunction(-1, -2), -3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
