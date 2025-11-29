#ifndef CURRENTANALYSIS_DYNAMIC_ARRAY_H
#define CURRENTANALYSIS_DYNAMIC_ARRAY_H

#include <format>
#include <ostream>
#include <cassert>

template<typename T>
class DynamicArray {
private:
    // Space for how many elements is allocated on realloc
    const int spacePerRealloc = 8;
    int availableLength = 0;

    void grow();

public:
    int Length = 0;
    T* Array;

    DynamicArray(int size);

    void Add(T value);
    T Get(int index);
    void Set(int index, T value);

};


template<typename T>
DynamicArray<T>::DynamicArray(int size) {
    assert(size >= 0);
    Array = new T[size];
    availableLength = size;
}

template<typename T>
void DynamicArray<T>::Add(T value) {
    if (Length+1 > availableLength) {
        grow();
    }

    Array[Length] = value;
    Length++;
}

template<typename T>
void DynamicArray<T>::Set(int index, T value) {
    assert(index < Length);
    Array[index] = value;
}

template<typename T>
T DynamicArray<T>::Get(int index) {
    assert(index < Length);
    return Array[index];
}

template<typename T>
void DynamicArray<T>::grow() {
    T* oldArray = Array;
    availableLength = Length + spacePerRealloc;
    T* newArray = new T[availableLength];

    for (int i = 0; i < Length; i++) {
        newArray[i] = oldArray[i];
    }

    delete[] oldArray;
    Array = newArray;
}


template<typename T>
std::ostream& operator<<(std::ostream& os, DynamicArray<T>& array)
{
    os << "[ ";
    for (int i = 0; i < array.Length; i++) {
        os << std::format("{:4}", array.Get(i));
    }
    os << " ]";

    return os;
}



#endif //CURRENTANALYSIS_DYNAMIC_ARRAY_H