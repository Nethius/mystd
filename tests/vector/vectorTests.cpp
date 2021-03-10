#include "gtest/gtest.h"
#include "vector/vector.h"
#include "list"
#include "vector"

TEST(vector_tests, default_constructor) {
    auto *vector = new mystd::vector<int>();
    EXPECT_NE(vector, nullptr);
}

TEST(vector_tests, constructor_with_count_default_inserted_instance_of_T) {
    auto *vector = new mystd::vector<int>(100);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), 100);
}

TEST(vector_tests, constructor_with_count_copies_of_given_value) {
    auto *vector = new mystd::vector<int>(100, 5);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), 100);
    for (auto v : *vector)
        EXPECT_EQ(v, 5);
}

TEST(vector_tests, range_based_constructor) {
    std::list<int> list{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>(list.begin(), list.end());
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), list.size());

    for (auto[l, v] = std::tuple{list.begin(), vector->begin()}; l != list.end(); l++, v++)
        EXPECT_EQ(*l, *v);
}

TEST(vector_tests, copy_constructor) {
    mystd::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>(base_vector);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, move_constructor) {
    mystd::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> copied_vector(base_vector);

    auto *vector = new mystd::vector<int>(std::move(base_vector));

    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), copied_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), copied_vector[i]);
    }
}

TEST(vector_tests, initializer_list_constructor) {
    std::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};

    auto *vector = new mystd::vector<int>{1, 2, 3, 4, 5, 6, 9, 22};

    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, assign_value) {
    auto *vector = new mystd::vector<int>;
    EXPECT_NE(vector, nullptr);
    vector->assign(10, 45);

    EXPECT_EQ(vector->size(), 10);

    for (auto v : *vector)
        EXPECT_EQ(v, 45);
}

TEST(vector_tests, assign_range) {
    auto *vector = new mystd::vector<int>;
    std::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};
    EXPECT_NE(vector, nullptr);
    vector->assign(base_vector.begin(), base_vector.end());

    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, copy_assignment_operator) {
    auto *vector = new mystd::vector<int>;
    mystd::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};

    EXPECT_NE(vector, nullptr);
    *vector = base_vector;

    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, move_assignment_operator) {
    mystd::vector<int> base_vector{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> copied_vector(base_vector);
    auto *vector = new mystd::vector<int>;

    EXPECT_NE(vector, nullptr);
    *vector = std::move(base_vector);

    EXPECT_EQ(vector->size(), copied_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), copied_vector[i]);
    }
}

TEST(vector_tests, access_operator) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> vector(v.begin(), v.end());

    EXPECT_EQ(v.size(), vector.size());

    for (size_t i = 0; i < v.size(); i++)
        EXPECT_EQ(vector[i], v[i]);
}

TEST(vector_tests, front) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> vector(v.begin(), v.end());

    EXPECT_EQ(v.size(), vector.size());

    EXPECT_EQ(vector.front(), v.front());
}

TEST(vector_tests, back) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> vector(v.begin(), v.end());

    EXPECT_EQ(v.size(), vector.size());

    EXPECT_EQ(vector.back(), v.back());
}

TEST(vector_tests, data) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};

    EXPECT_EQ(*(vector.data()), vector.front());

    EXPECT_EQ(*(vector.data() + vector.size() - 1), vector.back()); //not sure if this is correct
}

TEST(vector_tests, begin) {
    mystd::vector<int> v{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>;

    EXPECT_NE(vector, nullptr);

    EXPECT_EQ(vector->begin(), vector->end());

    *vector = v;

    EXPECT_EQ(*(vector->begin()), v[0]);
}

TEST(vector_tests, end) {
    mystd::vector<int> v{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>;

    EXPECT_NE(vector, nullptr);

    EXPECT_EQ(vector->begin(), vector->end());

    *vector = v;

    EXPECT_EQ(*(vector->end()), v[v.size()]);
}

TEST(vector_tests, empty) {
    mystd::vector<int> v{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>;

    EXPECT_EQ(vector->empty(), true);

    *vector = v;

    EXPECT_EQ(vector->empty(), false);
}

TEST(vector_tests, size) {
    mystd::vector<int> v{1, 2, 3, 4, 5, 6, 9, 22};
    auto *vector = new mystd::vector<int>;

    EXPECT_EQ(vector->size(), 0);

    *vector = v;

    EXPECT_EQ(vector->size(), v.size());
}

TEST(vector_tests, reserve) {
    mystd::vector<int> vector(20);

    EXPECT_EQ(vector.capacity(), 20);

    vector.reserve(10);

    EXPECT_EQ(vector.capacity(), 20);

    vector.reserve(30);

    EXPECT_EQ(vector.capacity(), 30);
}