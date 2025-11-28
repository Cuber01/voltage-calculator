#include <iostream>
#include "DynamicArray.h"

int main() {
    DynamicArray<int> array = DynamicArray<int>(1);
    array.Add(1);
    array.Add(2);
    array.Add(3);
    array.Add(4);
    array.Add(5);

    std::cout << array << std::endl;


    return 0;
}