#include <iostream>
#include "DynamicArray.h"
#include "Matrix.h"

int main() {
    auto* matrix = new DynamicMatrix<int>(5,5);
    matrix->Set(2,4,6);
    std::cout << matrix->Get(2,4) << std::endl;
    std::cout << *matrix << std::endl;
    delete matrix;

    return 0;
}