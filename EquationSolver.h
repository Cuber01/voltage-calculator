//
// Created by cubeq on 12/18/25.
//

#ifndef CURRENTANALYSIS_EQUATIONSOLVER_H
#define CURRENTANALYSIS_EQUATIONSOLVER_H
#include "Matrix.h"

template<typename T>
class EquationSolver {
    public:

    static void GaussElimination(DynamicMatrix<T>* expandedMatrix);
    DynamicMatrix<T>* BackSubstitution(DynamicMatrix<T>* gaussedMatrix);
};

template<typename T>
void EquationSolver<T>::GaussElimination(DynamicMatrix<T> *expandedMatrix) {
    int rows = expandedMatrix->GetLengthY();
    int cols = expandedMatrix->LengthX;

    for (int i = 0; i < rows - 1; i++) {
        for (int j = i + 1; j < rows; j++) {
            T factor = expandedMatrix->Get(j, i) / expandedMatrix->Get(i, i);

            for (int k = i; k < cols; k++) {
                T a_kj = expandedMatrix->Get(k, j);
                T a_ik = expandedMatrix->Get(k, i);

                expandedMatrix->Set(k, j, a_kj - (factor * a_ik));
            }
        }
    }
}


template<typename T>
DynamicMatrix<T>* EquationSolver<T>::BackSubstitution(DynamicMatrix<T> *gaussedMatrix) {
    int rows = gaussedMatrix->GetLengthY();
    int cols = gaussedMatrix->LengthX;
    DynamicMatrix<T>* solution = new DynamicMatrix<T>(1, rows);

    // Going from bottom to top
    for (int y = rows - 1; y >= 0; y--) {
        T sum = 0;

        // Sum already calculated unknowns
        for (int x = y + 1; x < rows; x++)
        {
            sum += gaussedMatrix->Get(x, y) * solution->Get(0,x);
        }

        T b_y = gaussedMatrix->Get(cols - 1, y); // wyraz wolny (intercept)
        T a_yy = gaussedMatrix->Get(y, y); // współczynnik na przekątnej (coefficient on the diagonal)

        solution->Set(0,y, (b_y - sum) / a_yy);
    }

    return solution;
}


#endif //CURRENTANALYSIS_EQUATIONSOLVER_H
