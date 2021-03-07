#include "gtest/gtest.h"
#include "vector/vector.h"
#include "list"
#include "vector"

TEST(vectorTests, default_constructor) {
    auto *vector = new mystd::vector<int>;
    EXPECT_NE(vector, nullptr);
}

TEST(vectorTests, constructor_with_count_default_inserted_instance_of_T) {
    auto *vector = new mystd::vector<int>(100);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), 100);
}

TEST(vectorTests, constructor_with_count_copies_of_given_value) {
    auto *vector = new mystd::vector<int>(100, 5);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), 100);
    for (auto v : *vector)
        EXPECT_EQ(v, 5);
}

TEST(vectorTests, range_based_constructor) {
    std::list<int> list{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>(list.begin(), list.end());
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), list.size());

    for (auto[l, v] = std::tuple{list.begin(), vector->begin()}; l != list.end(); l++, v++)
        EXPECT_EQ(*l, *v);
}

TEST(vectorTests, copy_constructor) {
    mystd::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>(base_vector);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++){
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vectorTests, move_constructor) {
    mystd::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> copied_vector(base_vector);

    auto *vector = new mystd::vector<int>(std::move(base_vector));

    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), copied_vector.size());

    for (size_t i = 0; i < vector->size(); i++){
        EXPECT_EQ(*(vector->begin() + i), copied_vector[i]);
        EXPECT_NE(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vectorTests, initializer_list_constructor) {
    std::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};

    auto *vector = new mystd::vector<int>{1, 2, 3, 4, 5, 6, 9, 22};

    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}