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

    // Loop through all columns and rows
    while (y <= rows && x <= cols) {

        // Find the pivot in column (maximum absolute value)
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
            // No pivot found (all zeros). Go to next column
            x++;
        }
        else {
            // Swap current row with row containing largest pivot
            expandedMatrix->SwapRows(y, maxIndex);

            // Eliminate entries below pivot in current column for all subsequent rows
            for (int i = y + 1; i < rows; i++) {

                // Elimination factor
                // Calculated so that "Get(x, i) - (Get(x, y) * f)" = 0 in (x,i)
                // czyli żeby element pod pivotem był równy zero (wtedy utworzy się "schodek")
                double f = expandedMatrix->Get(x, i) / expandedMatrix->Get(x, y);

                // Multiply all elements in current row by -f and then add (j,i) to them
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

        // Sum known terms
        double sum = 0;
        for (int x = y + 1; x < rows; x++)
        {
            // Podstawiamy solution * współczynnik i liczymy sumę znanych nam już niewiadomych
            sum += gaussedMatrix->Get(x, y) * solution->Get(0,x);
        }

        double b_y = gaussedMatrix->Get(cols - 1, y); // wyraz wolny (intercept) - czyli wartość po prawej stronie równania
        double a_yy = gaussedMatrix->Get(y, y); // współczynnik na przekątnej (coefficient on the diagonal) - czyli pivot danego rzędu

        // Na prawą stronę równania, razem z wyrazem wolnym, przesuwamy sumę znanych nam niewiadomych.
        // Następnie dzielimy przez współczynnik tak aby otrzymać wartość pojedynczej wartości niewiadomej
        solution->Set(0,y, (b_y - sum) / a_yy);
    }

    return solution;
}


#endif //CURRENTANALYSIS_EQUATIONSOLVER_H
