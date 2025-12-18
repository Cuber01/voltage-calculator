#include <iostream>
#include "DynamicArray.h"
#include "EquationSolver.h"
#include "InputReader.h"
#include "Matrix.h"

int main() {
     auto* input = new InputReader();
     auto* EquationSolver = new ::EquationSolver<double>();

     input->Read("input.txt");
     std::cout << *input->CurrentVector << std::endl;
     std::cout << *input->AdmittanceMatrix << std::endl;
     input->AdmittanceMatrix->AddColumn(input->CurrentVector);

     std::cout << *input->AdmittanceMatrix << std::endl;
     input->AdmittanceMatrix->PopRow(); // Uziemienie
     std::cout << *input->AdmittanceMatrix << std::endl;

     EquationSolver->GaussElimination(input->AdmittanceMatrix);
     std::cout << *input->AdmittanceMatrix << std::endl;

     delete input;
     return 0;
}