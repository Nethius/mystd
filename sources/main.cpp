#include <iostream>
#include "vector"
#include "vector/vector.h"

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    std::vector<int*> vector{&a, &b, &c, &d};

    mystd::vector<int*> myvector(vector.cbegin(), vector.cend());
    std::vector<int*> av(vector.cbegin(), vector.cend());
    for (auto v : myvector) {
        std::cout << *v << " ";
    }
    std::cout << std::endl;
    for (auto v : av) {
        std::cout << *v << " ";
    }
    std::cout << std::endl;
    for (auto v : vector) {
        std::cout << *v << " ";
    }
    std::cout << std::endl;
    vector.clear();
    for (auto v : myvector) {
        std::cout << *v << " ";
    }
    std::cout << std::endl;
    for (auto v : av) {
        std::cout << *v << " ";
    }
    std::cout << std::endl;
    for (auto v : vector) {
        std::cout << *v << " ";
    }
    std::cout << std::endl;
    return 0;
}
