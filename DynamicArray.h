#ifndef CURRENTANALYSIS_DYNAMIC_ARRAY_H
#define CURRENTANALYSIS_DYNAMIC_ARRAY_H

#include <format>
#include <ostream>
#include <cassert>
#include <iostream>

template<typename T>
class DynamicArray {
private:
    // Space for how many elements is allocated on realloc
    const int spacePerRealloc = 8;


    void grow();

public:
    int AvailableLength = 0;
    int Length = 0;
    T* Array;

    explicit DynamicArray(int size, bool filledWithZeros = false);
    DynamicArray(std::initializer_list<T> list);
    ~DynamicArray();

    void Add(T value);
    T Get(int index);
    void Set(int index, T value);
    void ResizeAndSet(int index, T value);

};


template<typename T>
DynamicArray<T>::DynamicArray(int size, bool filledWithZeros) {
    assert(size > 0);
    Array = new T[size];
    AvailableLength = size;

    if (filledWithZeros) {
        for (int i = 0; i < size; i++) {
            Add(0);
        }
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> list) {
    Array = new T[list.size()];
    AvailableLength = list.size();

    for (T value : list) {
        Add(value);
    }
    std::cout << Length << std::endl;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete Array;
}

template<typename T>
void DynamicArray<T>::Add(T value) {
    if (Length+1 > AvailableLength) {
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
void DynamicArray<T>::ResizeAndSet(int index, T value) {
    if (index < Length) {
        Array[index] = value;
    }
    else {
        while (index != Length) {
            Add(0);
        }
        Add(value);
    }
}

template<typename T>
T DynamicArray<T>::Get(int index) {
    assert(index < Length);
    return Array[index];
}

template<typename T>
void DynamicArray<T>::grow() {
    T* oldArray = Array;
    AvailableLength = Length + spacePerRealloc;
    T* newArray = new T[AvailableLength];

    for (int i = 0; i < Length; i++) {
        newArray[i] = oldArray[i];
    }

    delete oldArray;
    Array = newArray;
}


static std::string formatDouble(double value, int minWidth, int maxWidth) {
    std::string s = std::to_string(value);
    if (s.size() > maxWidth) s.resize(maxWidth);
    return std::format("{:>{}}", s, minWidth);
}

inline std::ostream& operator<<(std::ostream& os, DynamicArray<double>& array)
{
    os << "[ ";
    for (int i = 0; i < array.Length; i++) {
        if (array.Get(i) != 0)
            os << "\e[32m";

        os << formatDouble(array.Get(i), 6, 6);
        os << " \e[0m";
    }
    os << " ]";

    return os;
}




#endif //CURRENTANALYSIS_DYNAMIC_ARRAY_H