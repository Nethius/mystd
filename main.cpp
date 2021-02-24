#include <iostream>
#include "vector"
#include "sources/vector/vector.h"

int main() {

    const std::vector<int> vector{1, 2, 3, 4};

    mystd::vector<int> myvector(vector.cbegin(), vector.cend());

    for (auto v : myvector) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    std::vector<int> a(std::vector<int>(2, 5));
    for (auto v : a) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    mystd::vector<int> s(mystd::vector<int>{1, 2, 3, 4, 5});
//    s = myvector;
    s.shrink_to_fit();
    s.pop_back();
    for (auto v : s) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
//    myvector.assign(5, vector[3]);
//    for (auto v : myvector){
//        std::cout << v << " ";
//    }
//    std::cout << std::endl;
//    myvector.assign(vector.begin(), vector.end());
//    for (auto v : myvector){
//        std::cout << v << " ";
//    }
//    std::cout << std::endl;

    return 0;
}
