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

TEST(vector_tests, capacity) {
    mystd::vector<int> vector(20);

    EXPECT_EQ(vector.capacity(), 20);

    vector.push_back(1);

    EXPECT_EQ(vector.capacity(), static_cast<size_t>(20 * 1.5));
}

TEST(vector_tests, shrink_to_fit) {
    mystd::vector<int> vector(20);

    EXPECT_EQ(vector.capacity(), 20);

    vector.push_back(1);

    EXPECT_EQ(vector.capacity(), static_cast<size_t>(20 * 1.5));

    vector.shrink_to_fit();

    EXPECT_EQ(vector.capacity(), vector.size());
}

TEST(vector_tests, clear) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};
    auto capacity = vector.capacity();

    vector.clear();

    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(vector.capacity(), capacity);
}

TEST(vector_tests, insert_copy) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};

    auto it = vector.begin() + 2;
    int value = 66;
    auto res = vector.insert(it, value);

    EXPECT_EQ(*res, value);
    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_move) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};

    auto it = vector.begin() + 2;
    auto res = vector.insert(it, 66);

    EXPECT_EQ(*res, 66);
    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_count_copies) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};

    auto it = vector.begin() + 2;
    int value = 66;
    auto res = vector.insert(it, 10, value);

    for (auto i = res; i < res + 10; i++)
        EXPECT_EQ(*i, value);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);

    res = vector.insert(it, 0, value);
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_range) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};
    std::vector<int> v{11, 12, 13, 14, 15};

    auto size = vector.size();
    auto it = vector.begin() + 2;
    auto res = vector.insert(it, v.begin(), v.end());

    for (auto[i, j] = std::tuple{res, v.begin()}; i < res + v.size(); i++, j++)
        EXPECT_EQ(*i, *j);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
    EXPECT_EQ(vector.capacity(), static_cast<size_t>((size + v.size()) * 1.5));

    res = vector.insert(it, v.begin(), v.begin());
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_initializer_list) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};
    std::vector<int> v{11, 12, 13, 14, 15};

    auto size = vector.size();
    auto it = vector.begin() + 2;
    auto res = vector.insert(it, {11, 12, 13, 14, 15});

    for (auto[i, j] = std::tuple{res, v.begin()}; i < res + v.size(); i++, j++)
        EXPECT_EQ(*i, *j);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
    EXPECT_EQ(vector.capacity(), static_cast<size_t>((size + v.size()) * 1.5));

    res = vector.insert(it, {});
    EXPECT_EQ(res, it);
}

TEST(vector_tests, emplace) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};

    auto it = vector.begin() + 2;
    int value = 66;
    auto res = vector.emplace(it, value);

    EXPECT_EQ(*res, value);
    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
}

TEST(vector_tests, erase_element) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> v{1, 2, 4, 5, 6, 9, 22};

    auto it = vector.begin() + 2;
    auto res = vector.erase(it);

    EXPECT_EQ(vector.size(), v.size());
    for (size_t i = 0; i < vector.size(); i++)
        EXPECT_EQ(vector[i], v[i]);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);

    auto last = vector.end() - 1;
    res = vector.erase(last);

    EXPECT_EQ(res, vector.end());
}

TEST(vector_tests, erase_elements) {
    mystd::vector<int> vector{1, 2, 3, 4, 5, 6, 9, 22};
    mystd::vector<int> v{1, 2, 22};

    auto it = vector.begin() + 2;
    auto res = vector.erase(it, it + 4);

    EXPECT_EQ(vector.size(), v.size());
    for (size_t i = 0; i < vector.size(); i++)
        EXPECT_EQ(vector[i], v[i]);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);

    auto second = vector.begin() + 1;
    auto last = vector.end() - 1;
    res = vector.erase(second, last);

    EXPECT_EQ(res, vector.end());

}