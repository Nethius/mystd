#include <iostream>
#include "vector"
#include "sources/vector/vector.h"
int main() {

    const std::vector<int> vector {1, 2, 3, 4};
    mystd::vector<int> avector {1, 2, 3, 4};
    std::vector<int> v = vector;
//    v[0] = 10;
    mystd::vector<int> myvector(avector);
//    myvector = avector;

    auto begin = myvector.begin();
    auto vbegin = vector.cbegin();
    begin++;
    auto end = myvector.end();

    for (auto v : myvector){
        std::cout << v << std::endl;
    }

    std::cout << vector.front() << " " << myvector.front() << std::endl;
    return 0;
}
