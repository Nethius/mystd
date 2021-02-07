#include <iostream>
#include "vector"
#include "sources/vector/vector.h"
int main() {

    std::vector<int> vector {1, 2, 3, 4};
    mystd::vector<int> myvector {1, 2, 3, 4};

    auto begin = myvector.begin();
    begin++;
    auto end = myvector.end();

    for (auto v : myvector){
        std::cout << v << std::endl;
    }

    std::cout << vector[0] << " " << myvector[0] << std::endl;
    return 0;
}
