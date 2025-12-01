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

    auto* n = new DynamicArray<double>(8);
    auto* v = new DynamicMatrix<double>(1,1);
    v->AddRow(n);
    std::cout << *v << std::endl;
    delete v;

    return 0;
}