// Copyright 2022 OUEIO

#include <gtest/gtest.h>

TEST(test, test) {
    EXPECT_EQ(std::max(1, 2), 2);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
