#include <iostream>
#include "vector"
#include "sources/vector/vector.h"
int main() {

    const std::vector<int> vector {1, 2, 3, 4};
    const mystd::vector<int> avector {1, 2, 3, 4};
    std::vector<int> v = vector;
//    v[0] = 10;
    mystd::vector<int> myvector(avector);
    std::cout << myvector.size() << std::endl;
    myvector.push_back(10);
    std::cout << myvector.size() << std::endl;
    v.push_back(20);
    v.push_back(40);
    v.push_back(50);
//    myvector = avector;

    auto begin = myvector.begin();
    auto vbegin = vector.cbegin();
    auto t = vector.end();
    begin++;
    auto end = myvector.end();
    std::cout << v.capacity() << std::endl;
    for (auto v : myvector){
        std::cout << v << std::endl;
    }

    std::cout << vector.front() << " " << myvector.front() << std::endl;
    return 0;
}
