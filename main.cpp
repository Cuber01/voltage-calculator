#include <iostream>
#include "DynamicArray.h"
#include "InputReader.h"
#include "Matrix.h"

int main() {
    auto* input = new InputReader();
    input->Read("input.txt");
    std::cout << *input->VoltageVector << std::endl;
    std::cout << *input->AdmittanceMatrix << std::endl;
    delete input;

    return 0;
}