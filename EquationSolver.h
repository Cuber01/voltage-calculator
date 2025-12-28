//
// Created by cubeq on 12/18/25.
//

#ifndef CURRENTANALYSIS_EQUATIONSOLVER_H
#define CURRENTANALYSIS_EQUATIONSOLVER_H
#include <math.h>

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

    int y = 0; // row
    int x = 0; // column

    while (y <= rows && x <= cols) {

        // Find the pivot in column
        int maxIndex = -1;
        double maximum = -INFINITY;
        for (int i = y; i < rows; i++) {
            double value = abs(expandedMatrix->Get(x,i));
            if (value > maximum) {
                maximum = value;
                maxIndex = i;
            }
        }

        if (maxIndex == -1) {
            // No pivot found. Go to next column
            x++;
        }
        else {
            expandedMatrix->SwapRows(y, maxIndex);

            for (int i = y + 1; i < rows; i++) {

                // Elimination factor
                // Calculated so that "Get(x, i) - (Get(x, y) * f)" = 0 in (x,i)
                double f = expandedMatrix->Get(x, i) / expandedMatrix->Get(x, y);

                // Fill with zeros the lower part of pivot column
                expandedMatrix->Set(x,i,0);

                // Do for all remaining elements in current row
                for (int j = x + 1; j < cols; j++) {
                    expandedMatrix->Set(j, i, expandedMatrix->Get(j, i) - expandedMatrix->Get(j, x) * f);
                }
            }
            y++;
            x++;
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
