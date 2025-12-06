#include <iostream>
#include "DynamicArray.h"
#include "InputReader.h"
#include "Matrix.h"

int main() {
    // auto* input = new InputReader();
    // input->Read("input.txt");
    // std::cout << *input->VoltageVector << std::endl;
    // std::cout << *input->AdmittanceMatrix << std::endl;
    // delete input;

    //auto* arr = new DynamicMatrix<double>({{1,2,3},{4,5,6}});

    DynamicMatrix<double> m = {{{1,2}, {3,4}}};
    DynamicMatrix<double> d = {{{1,2,3}, {4,5,6}}};
    std::cout << m;
    std::cout << d;



    DynamicMatrix<double> md = m*d;
    std::cout << md;

    return 0;
}