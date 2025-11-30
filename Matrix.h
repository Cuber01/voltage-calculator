#ifndef CURRENTANALYSIS_MATRIX_H
#define CURRENTANALYSIS_MATRIX_H

#include "DynamicArray.h"
#include <cassert>

template<typename T>
class DynamicMatrix {
    const int spacePerRealloc = 4;

    void grow();
    void readjustRowsSize();
    void checkAndReadjust(DynamicArray<T>* row);

public:
    int Length = 0;
    int LengthX = 0;

    DynamicMatrix(int sizeX, int sizeY);
    ~DynamicMatrix();

    DynamicArray< DynamicArray<T>* >* PtrArray = nullptr;

    void AddRow(DynamicArray<T>* row);
    void AddEmptyRows(int amount, int size);
    T Get(int x, int y);
    DynamicArray<T>* GetRow(int y);
    void Set(int x, int y, T value);
};

template<typename T>
DynamicMatrix<T>::DynamicMatrix(int sizeX, int sizeY) {
    assert(sizeX >= 0 && sizeY >= 0);
    PtrArray = new DynamicArray< DynamicArray<T>* >(sizeY);
    LengthX = sizeX;
    AddEmptyRows(sizeY, sizeX);
}

template<typename T>
DynamicMatrix<T>::~DynamicMatrix() {
    for (int i = 0; i < Length; i++) {
        delete PtrArray->Array[i];
    }
    delete PtrArray;
}

template<typename T>
void DynamicMatrix<T>::AddRow(DynamicArray<T>* row) {
    if (Length+1 > PtrArray->AvailableLength) {
        grow();
    }

    PtrArray->Add(row);
    Length++;

    checkAndReadjust(row);
}

template<typename T>
void DynamicMatrix<T>::AddEmptyRows(int amount, int size) {
    while (amount > 0) {
        AddRow(new DynamicArray<T>(size));
        amount--;
    }

}

template<typename T>
DynamicArray<T>* DynamicMatrix<T>::GetRow(int y) {
    assert(y < Length);
    return PtrArray->Get(y);
}

template<typename T>
T DynamicMatrix<T>::Get(int x, int y) {
    assert(y < Length && x < PtrArray[y].Length);
    return PtrArray->Get(y)->Get(x);
}

template<typename T>
void DynamicMatrix<T>::Set(int x, int y, T value) {
    assert(y < Length && x < PtrArray[y].Length);
    PtrArray->Get(y)->Set(x, value);
}


template<typename T>
void DynamicMatrix<T>::grow() {
    DynamicArray< DynamicArray<T>* >* oldArray = PtrArray;
    int newLength = Length + spacePerRealloc;
    auto* newArray = new DynamicArray< DynamicArray<T>* >(newLength);

    for (int i = 0; i < Length; i++) {
        newArray->Add(oldArray->Get(i));
    }

    delete[] oldArray;
    PtrArray = newArray;
}

template<typename T>
void DynamicMatrix<T>::readjustRowsSize() {
    for (int i = 0; i < Length; i++) {
        DynamicArray<T>* row = GetRow(i);
        while (row->Length < LengthX) {
            row->Add(0);
        }
    }
}

template<typename T>
void DynamicMatrix<T>::checkAndReadjust(DynamicArray<T>* row) {
    if (row->Length != LengthX) {
        if (row->Length > LengthX) {
            LengthX = row->Length;
        }

        readjustRowsSize();
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DynamicMatrix<T>& matrix)
{
    os << "{ ";
    for (int i = 0; i < matrix.Length; i++) {
        os << "\n";
        os << *matrix.GetRow(i);
    }
    os << "\n}";

    return os;
}



#endif //CURRENTANALYSIS_MATRIX_H
