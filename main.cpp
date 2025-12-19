#include <iostream>
#include "DynamicArray.h"
#include "EquationSolver.h"
#include "InputReader.h"
#include "Matrix.h"

int main() {
     auto* input = new InputReader();
     auto* equationSolver = new ::EquationSolver<double>();

     // Read input
     input->Read("input.txt");
     std::cout << "Vector of currents:" << std::endl;
     std::cout << *input->CurrentVector << std::endl;
     std::cout << "Admittance matrix:" << std::endl;
     std::cout << *input->AdmittanceMatrix << std::endl;

     // Add CurrentVector to AdmittanceMatrix for use in equation solving
     DynamicMatrix<double>* equationMatrix = input->AdmittanceMatrix;
     equationMatrix->AddColumn(input->CurrentVector);

     // Uziemienie
     equationMatrix->PopRow();
     std::cout << "Equation matrix after grounding the last node:" << std::endl;
     std::cout << *equationMatrix << std::endl;

     // Do gauss elimination
     equationSolver->GaussElimination(equationMatrix);
     std::cout << "After gauss elimination:" << std::endl;
     std::cout << *equationMatrix << std::endl;

     // Solve gauss eliminated matrix
     DynamicMatrix<double>* voltageVector = equationSolver->BackSubstitution(equationMatrix);
     voltageVector->AddEmptyRows(1,1);
     std::cout << "Voltage vector (with grounded node included):" << std::endl;
     std::cout << *voltageVector << std::endl;

     delete input;
     delete equationSolver;
     delete voltageVector;
     return 0;
}