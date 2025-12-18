//
// Created by cubeq on 12/18/25.
//

#ifndef CURRENTANALYSIS_EQUATIONSOLVER_H
#define CURRENTANALYSIS_EQUATIONSOLVER_H
#include "Matrix.h"

template<typename T>
class EquationSolver {
    static void GaussElimination(DynamicMatrix<T>* matrixToEliminate);
};

template<typename T>
void EquationSolver<T>::GaussElimination(DynamicMatrix<T> *expandedMatrix) {
    int length = expandedMatrix->GetLengthY();

    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            double factor = expandedMatrix->Get(i,j) / expandedMatrix->Get(i,i);

            for (int k = i; k <= length; k++)
            {
                expandedMatrix->Set(k,j, expandedMatrix->Get(j,k) - (factor * expandedMatrix->Get(k,i)));
            }
        }
    }
}


#endif //CURRENTANALYSIS_EQUATIONSOLVER_H
