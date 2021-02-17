#include <iostream>
#include "vector"
#include "sources/vector/vector.h"
int main() {

    std::vector<int> vector {1, 2, 3, 4};
//    mystd::vector<int> myvector {1, 2, 3, 4};

    int v1 = 20;
    vector.push_back(10);
//    myvector.push_back(10);
    vector.push_back(v1);
//    myvector.push_back(v1);
    mystd::vector<int> myvector(vector.cbegin(), vector.cend());
    mystd::vector<int> s(myvector.begin(), myvector.end());
    int t = 11;
    vector.emplace(vector.begin(), 10);
    auto it = s.begin() + 1;
    s.emplace(it, 10);
    for (auto v : s){
        std::cout << v << " ";
    }
    std::cout << std::endl;
    it = s.begin() + 1;
    s.insert(it, t);
    for (auto v : s){
        std::cout << v << " ";
    }

    for (size_t i = 0; i < myvector.size(); i++){
        if (vector[i] != myvector[i])
            std::cout << "not same" << std::endl;
    }
    std::cout << "same" << std::endl;

    return 0;
}
