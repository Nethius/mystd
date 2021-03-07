#include "gtest/gtest.h"
#include "vector/vector.h"

TEST(vectorTests, defaultConstructor) {
    auto* vector = new mystd::vector<int>;
    EXPECT_TRUE(vector != nullptr);
}