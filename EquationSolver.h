//
// Created by cubeq on 12/18/25.
//

#ifndef CURRENTANALYSIS_EQUATIONSOLVER_H
#define CURRENTANALYSIS_EQUATIONSOLVER_H
#include "Matrix.h"

template<typename T>
class EquationSolver {
    public:

    static void GaussElimination(DynamicMatrix<T>* matrixToEliminate);
};

template<typename T>
void EquationSolver<T>::GaussElimination(DynamicMatrix<T> *expandedMatrix) {
    int rows = expandedMatrix->GetLengthY();
    int cols = expandedMatrix->LengthX;

    for (int i = 0; i < rows - 1; i++) {
        for (int j = i + 1; j < rows; j++) {

            double factor = (double)expandedMatrix->Get(i, j) / expandedMatrix->Get(i, i);

            for (int k = i; k < cols; k++) {
                T a_jk = expandedMatrix->Get(k, j);
                T a_ik = expandedMatrix->Get(k, i);

                expandedMatrix->Set(k, j, a_jk - (factor * a_ik));
            }
        }
    }
}




#endif //CURRENTANALYSIS_EQUATIONSOLVER_H
