#include <iostream>
#include "vector"
#include "sources/vector/vector.h"
int main() {

    std::vector<int> vector {1, 2, 3, 4};
    mystd::vector<int> myvector {1, 2, 3, 4};

    std::cout << vector[0] << " " << myvector[0] << std::endl;
    return 0;
}
