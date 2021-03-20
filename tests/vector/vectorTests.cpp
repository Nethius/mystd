#include "gtest/gtest.h"
#include "vector/vector.h"
#include "list"
#include "vector"
#include "string"

struct TestData {
    int _intValue;
    std::string _stringValue;

    TestData() : _intValue(0), _stringValue("") {};

    TestData(int intValue, std::string stringValue) : _intValue(intValue), _stringValue(std::move(stringValue)) {}

    bool operator==(const TestData& other) const {
        return ((_intValue == other._intValue) && (_stringValue == other._stringValue));
    }

    bool operator!=(const TestData& other) const {
        return !(*this == other);
    }

    TestData& operator=(const TestData& other) {
        _intValue = other._intValue;
        _stringValue.resize(other._stringValue.size());
        _stringValue = other._stringValue;
        return *this;
    };
};

TEST(vector_tests, default_constructor) {
    auto* vector = new mystd::vector<TestData>();
    EXPECT_NE(vector, nullptr);
}

TEST(vector_tests, constructor_with_count_default_inserted_instance_of_T) {
    auto* vector = new mystd::vector<TestData>(100);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), 100);
}

TEST(vector_tests, constructor_with_count_copies_of_given_value) {
    TestData testData(1, "one");
    auto* vector = new mystd::vector<TestData>(100, testData);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), 100);
    for (const auto& v : *vector)
        EXPECT_EQ(v, testData);
}

TEST(vector_tests, range_based_constructor) {
    std::list<TestData> list{{1, "one"},
                             {2, "two"},
                             {3, "three"}};
    auto* vector = new mystd::vector<TestData>(list.begin(), list.end());
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), list.size());

    for (auto[l, v] = std::tuple{list.begin(), vector->begin()}; l != list.end(); l++, v++)
        EXPECT_EQ(*l, *v);
}

TEST(vector_tests, copy_constructor) {
    mystd::vector<TestData> base_vector{{1, "one"},
                                        {2, "two"},
                                        {3, "three"}};
    auto* vector = new mystd::vector<TestData>(base_vector);
    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, move_constructor) {
    mystd::vector<TestData> base_vector{{1, "one"},
                                        {2, "two"},
                                        {3, "three"}};
    mystd::vector<TestData> copied_vector(base_vector);

    auto* vector = new mystd::vector<TestData>(std::move(base_vector));

    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), copied_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), copied_vector[i]);
    }
}

TEST(vector_tests, initializer_list_constructor) {
    std::vector<TestData> base_vector{{1, "one"},
                                      {2, "two"},
                                      {3, "three"}};

    auto* vector = new mystd::vector<TestData>{{1, "one"},
                                               {2, "two"},
                                               {3, "three"}};

    EXPECT_NE(vector, nullptr);
    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, assign_value) {
    TestData testData(1, "one");
    auto* vector = new mystd::vector<TestData>;
    EXPECT_NE(vector, nullptr);
    vector->assign(10, testData);

    EXPECT_EQ(vector->size(), 10);

    for (const auto& v : *vector)
        EXPECT_EQ(v, testData);
}

TEST(vector_tests, assign_range) {
    auto* vector = new mystd::vector<TestData>;
    std::vector<TestData> base_vector{{1, "one"},
                                      {2, "two"},
                                      {3, "three"}};
    EXPECT_NE(vector, nullptr);
    vector->assign(base_vector.begin(), base_vector.end());

    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, copy_assignment_operator) {
    auto* vector = new mystd::vector<TestData>;
    mystd::vector<TestData> base_vector{{1, "one"},
                                        {2, "two"},
                                        {3, "three"}};

    EXPECT_NE(vector, nullptr);
    *vector = base_vector;

    EXPECT_EQ(vector->size(), base_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), base_vector[i]);
    }
}

TEST(vector_tests, move_assignment_operator) {
    mystd::vector<TestData> base_vector{{1, "one"},
                                        {2, "two"},
                                        {3, "three"}};
    mystd::vector<TestData> copied_vector(base_vector);
    auto* vector = new mystd::vector<TestData>;

    EXPECT_NE(vector, nullptr);
    *vector = std::move(base_vector);

    EXPECT_EQ(vector->size(), copied_vector.size());

    for (size_t i = 0; i < vector->size(); i++) {
        EXPECT_EQ(*(vector->begin() + i), copied_vector[i]);
    }
}

TEST(vector_tests, access_operator) {
    std::vector<TestData> v{{1, "one"},
                            {2, "two"},
                            {3, "three"}};
    mystd::vector<TestData> vector(v.begin(), v.end());

    EXPECT_EQ(v.size(), vector.size());

    for (size_t i = 0; i < v.size(); i++)
        EXPECT_EQ(vector[i], v[i]);
}

TEST(vector_tests, front) {
    std::vector<TestData> v{{1, "one"},
                            {2, "two"},
                            {3, "three"}};
    mystd::vector<TestData> vector(v.begin(), v.end());

    EXPECT_EQ(v.size(), vector.size());

    EXPECT_EQ(vector.front(), v.front());
}

TEST(vector_tests, back) {
    std::vector<TestData> v{{1, "one"},
                            {2, "two"},
                            {3, "three"}};
    mystd::vector<TestData> vector(v.begin(), v.end());

    EXPECT_EQ(v.size(), vector.size());

    EXPECT_EQ(vector.back(), v.back());
}

TEST(vector_tests, data) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    EXPECT_EQ(*(vector.data()), vector.front());

    EXPECT_EQ(*(vector.data() + vector.size() - 1), vector.back()); //not sure if this is correct
}

TEST(vector_tests, begin) {
    mystd::vector<TestData> v{{1, "one"},
                              {2, "two"},
                              {3, "three"}};
    auto* vector = new mystd::vector<TestData>;

    EXPECT_NE(vector, nullptr);

    EXPECT_EQ(vector->begin(), vector->end());

    *vector = v;

    EXPECT_EQ(*(vector->begin()), v[0]);
}

TEST(vector_tests, end) {
    mystd::vector<TestData> v{{1, "one"},
                              {2, "two"},
                              {3, "three"}};
    auto* vector = new mystd::vector<TestData>;

    EXPECT_NE(vector, nullptr);

    EXPECT_EQ(vector->begin(), vector->end());

    *vector = v;

    EXPECT_EQ(*(vector->end() - 1), v[v.size() - 1]);
}

TEST(vector_tests, empty) {
    mystd::vector<TestData> v{{1, "one"},
                              {2, "two"},
                              {3, "three"}};
    auto* vector = new mystd::vector<TestData>;

    EXPECT_EQ(vector->empty(), true);

    *vector = v;

    EXPECT_EQ(vector->empty(), false);
}

TEST(vector_tests, size) {
    mystd::vector<TestData> v{{1, "one"},
                              {2, "two"},
                              {3, "three"}};
    auto* vector = new mystd::vector<TestData>;

    EXPECT_EQ(vector->size(), 0);

    *vector = v;

    EXPECT_EQ(vector->size(), v.size());
}

TEST(vector_tests, reserve) {
    mystd::vector<TestData> vector(20);

    EXPECT_EQ(vector.capacity(), 20);

    vector.reserve(10);

    EXPECT_EQ(vector.capacity(), 20);

    vector.reserve(30);

    EXPECT_EQ(vector.capacity(), 30);
}

TEST(vector_tests, capacity) {
    mystd::vector<TestData> vector(20);

    EXPECT_EQ(vector.capacity(), 20);

    vector.push_back({1, "one"});

    EXPECT_EQ(vector.capacity(), static_cast<size_t>(20 * 2));
}

TEST(vector_tests, shrink_to_fit) {
    mystd::vector<TestData> vector(20);

    EXPECT_EQ(vector.capacity(), 20);

    vector.push_back({1, "one"});

    EXPECT_EQ(vector.capacity(), static_cast<size_t>(20 * 2));

    vector.shrink_to_fit();

    EXPECT_EQ(vector.capacity(), vector.size());
}

TEST(vector_tests, clear) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};
    auto capacity = vector.capacity();

    vector.clear();

    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(vector.capacity(), capacity);
}

TEST(vector_tests, insert_copy) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    auto it = vector.begin() + 2;
    TestData testData(4, "four");
    auto res = vector.insert(it, testData);

    EXPECT_EQ(*res, testData);
    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_move) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    auto it = vector.begin() + 2;
    TestData testData(4, "four");
    auto res = vector.insert(it, std::move(testData));

    EXPECT_EQ(*res, TestData(4, "four"));
    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_count_copies) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    auto it = vector.begin() + 2;
    TestData testData(4, "four");
    auto res = vector.insert(it, 10, testData);

    for (auto i = res; i < res + 10; i++)
        EXPECT_EQ(*i, testData);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);

    res = vector.insert(it, 0, testData);
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_range) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};
    std::vector<TestData> v{{4, "four"},
                            {5, "five"},
                            {6, "six"}};

    auto size = vector.size();
    auto it = vector.begin() + 2;
    auto res = vector.insert(it, v.begin(), v.end());

    for (auto[i, j] = std::tuple{res, v.begin()}; i < res + v.size(); i++, j++)
        EXPECT_EQ(*i, *j);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
    EXPECT_EQ(vector.capacity(), static_cast<size_t>((size + v.size()) * 2));

    res = vector.insert(it, v.begin(), v.begin());
    EXPECT_EQ(res, it);
}

TEST(vector_tests, insert_initializer_list) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};
    std::vector<TestData> v{{4, "four"},
                            {5, "five"},
                            {6, "six"}};

    auto size = vector.size();
    auto it = vector.begin() + 2;
    auto res = vector.insert(it, {{4, "four"},
                                  {5, "five"},
                                  {6, "six"}});

    for (auto[i, j] = std::tuple{res, v.begin()}; i < res + v.size(); i++, j++)
        EXPECT_EQ(*i, *j);

    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
    EXPECT_EQ(vector.capacity(), static_cast<size_t>((size + v.size()) * 2));

    res = vector.insert(it, {});
    EXPECT_EQ(res, it);
}

TEST(vector_tests, emplace) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    auto it = vector.begin() + 2;
    TestData testData(4, "four");
    auto res = vector.emplace(it, testData);

    EXPECT_EQ(*res, testData);
    it = vector.begin() + 2;
    EXPECT_EQ(res, it);
}

TEST(vector_tests, erase_element) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};
    mystd::vector<TestData> v{{1, "one"},
                              {2, "two"}};

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
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"},
                                   {4, "four"},
                                   {5, "five"},
                                   {6, "six"}};
    mystd::vector<TestData> v{{1, "one"},
                              {2, "two"},
                              {6, "six"}};

    auto it = vector.begin() + 2;
    auto res = vector.erase(it, it + 2);

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

TEST(vector_tests, push_back_copy) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    TestData testData(4, "four");
    auto size = vector.size();
    vector.push_back(testData);

    EXPECT_EQ(vector.back(), testData);

    EXPECT_EQ(vector.capacity(), static_cast<size_t>(size * 2));
}

TEST(vector_tests, push_back_move) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    TestData testData(4, "four");
    auto size = vector.size();
    vector.push_back(std::move(testData));

    EXPECT_EQ(vector.back(), TestData(4, "four"));

    EXPECT_EQ(vector.capacity(), static_cast<size_t>(size * 2));
}

TEST(vector_tests, emplace_back) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    TestData testData(4, "four");
    auto size = vector.size();
    vector.emplace_back(testData);

    EXPECT_EQ(vector.back(), testData);

    EXPECT_EQ(vector.capacity(), static_cast<size_t>(size * 2));
}

TEST(vector_tests, pop_back) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    auto size = vector.size();
    vector.pop_back();

    EXPECT_EQ(vector.size(), size - 1);
}

TEST(vector_tests, resize) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"},
                                   {1, "one"},
                                   {2, "two"},
                                   {3, "three"}};
    std::vector<TestData> base_vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};
    vector.resize(10);

    EXPECT_EQ(vector.size(), 10);

    vector.resize(3);

    EXPECT_EQ(vector.size(), 3);

    for (size_t i = 0; i < vector.size(); i++)
        EXPECT_EQ(vector[i], base_vector[i]);
}

TEST(vector_tests, resize_with_value) {
    mystd::vector<TestData> vector;

    TestData testData(4, "four");
    vector.resize(10, testData);

    EXPECT_EQ(vector.size(), 10);

    for (const auto& v : vector)
        EXPECT_EQ(v, testData);

    vector.resize(5, testData);

    EXPECT_EQ(vector.size(), 5);
}

TEST(vector_tests, operators) {
    mystd::vector<TestData> vector{{1, "one"},
                                   {2, "two"},
                                   {3, "three"}};

    mystd::vector<TestData> v{{4, "four"},
                              {5, "five"},
                              {6, "six"}};

    EXPECT_EQ(true, vector != v);
}