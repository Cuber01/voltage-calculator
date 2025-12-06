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
    int LengthX = 0;

    DynamicMatrix(int sizeX, int sizeY);
    DynamicMatrix(std::initializer_list<std::initializer_list<T>> list);
    ~DynamicMatrix();

    DynamicArray< DynamicArray<T>* >* PtrArray = nullptr;

    void AddRow(DynamicArray<T>* row);
    void AddEmptyRows(int amount, int size);
    T Get(int x, int y);
    T TryGet(int x, int y);
    DynamicArray<T>* GetRow(int y);
    void Set(int x, int y, T value);
    void ResizeAndSet(int x, int y, T value);
    int GetLengthY();
};

template<typename T>
DynamicMatrix<T>::DynamicMatrix(int sizeX, int sizeY) {
    assert(sizeX >= 0 && sizeY >= 0);
    PtrArray = new DynamicArray< DynamicArray<T>* >(sizeY);
    LengthX = sizeX;
    AddEmptyRows(sizeY, sizeX);
}

template<typename T>
DynamicMatrix<T>::DynamicMatrix(std::initializer_list<std::initializer_list<T>> list) {
    PtrArray = new DynamicArray< DynamicArray<T>* >(list.size());
    LengthX = list.begin()->size();

    for (std::initializer_list<T> value : list) {
        assert(value.size() == LengthX);
        AddRow(new DynamicArray<T>(value));
    }
}

template<typename T>
DynamicMatrix<T>::~DynamicMatrix() {
    for (int i = 0; i < PtrArray->Length; i++) {
        delete PtrArray->Array[i];
    }
    delete PtrArray;
}

template<typename T>
void DynamicMatrix<T>::AddRow(DynamicArray<T>* row) {
    if (PtrArray->Length+1 > PtrArray->AvailableLength) {
        grow();
    }

    PtrArray->Add(row);

    checkAndReadjust(row);
}

template<typename T>
void DynamicMatrix<T>::AddEmptyRows(int amount, int size) {
    assert(size > 0);
    while (amount > 0) {
        AddRow(new DynamicArray<T>(size, true));
        amount--;
    }

}

template<typename T>
DynamicArray<T>* DynamicMatrix<T>::GetRow(int y) {
    assert(y < PtrArray->Length);
    return PtrArray->Get(y);
}

template<typename T>
T DynamicMatrix<T>::Get(int x, int y) {
    //assert(y < PtrArray->Length && x < PtrArray[y].Length);
    return PtrArray->Get(y)->Get(x);
}

template<typename T>
T DynamicMatrix<T>::TryGet(int x, int y) {
    if(y >= PtrArray->Length || x >= PtrArray->Get(y)->Length) {
        return T {};
    }
    return PtrArray->Get(y)->Get(x);
}

template<typename T>
void DynamicMatrix<T>::Set(int x, int y, T value) {
    //assert(y < PtrArray->Length && x < PtrArray[y].Length);
    PtrArray->Get(y)->Set(x, value);
}

template<typename T>
void DynamicMatrix<T>::ResizeAndSet(int x, int y, T value) {
    if (y < PtrArray->Length) {
        PtrArray->Get(y)->ResizeAndSet(x, value);
    }
    else {
        while (y != PtrArray->Length -1) {
            AddEmptyRows(1,x+1);
        }
        PtrArray->Get(y)->ResizeAndSet(x, value);
    }
}

template<typename T>
void DynamicMatrix<T>::grow() {
    DynamicArray< DynamicArray<T>* >* oldArray = PtrArray;
    int newLength = PtrArray->Length + spacePerRealloc;
    auto* newArray = new DynamicArray< DynamicArray<T>* >(newLength);

    for (int i = 0; i < PtrArray->Length; i++) {
        newArray->Add(oldArray->Get(i));
    }

    delete oldArray;
    PtrArray = newArray;
}

template<typename T>
void DynamicMatrix<T>::readjustRowsSize() {
    for (int i = 0; i < PtrArray->Length; i++) {
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
int DynamicMatrix<T>::GetLengthY() {
    return PtrArray->Length;
}


template<typename T>
std::ostream& operator<<(std::ostream& os, DynamicMatrix<T>& matrix)
{
    os << "{ ";
    for (int i = 0; i < matrix.PtrArray->Length; i++) {
        os << "\n";
        os << *matrix.GetRow(i);
    }
    os << "\n}";

    return os;
}


inline DynamicMatrix<double> operator*(DynamicMatrix<double>& a, DynamicMatrix<double>& b)
{
    assert(a.LengthX == b.GetLengthY() && "These matrixes cannot be multiplied.");

    int multMax = a.LengthX;
    int Xmax = b.LengthX;
    int Ymax = a.GetLengthY();

    DynamicMatrix<double>* result = new DynamicMatrix<double>(Xmax, Ymax);

    // Iterate over entire result table
    for (int x = 0; x < Xmax; x++) {
        for (int y = 0; y < Ymax; y++) {

            double value = 0;

            // Iterate over every relevant number in a and b to calculate value
            for (int currentMultIndex = 0; currentMultIndex < multMax; currentMultIndex++) {
                value += a.Get(currentMultIndex,y)*b.Get(x,currentMultIndex);
            }

            result->Set(x, y, value);
        }
    }

    return *result;
}



#endif //CURRENTANALYSIS_MATRIX_H
