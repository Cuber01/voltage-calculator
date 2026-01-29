#include "InputReader.h"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

InputReader::InputReader() {
    CurrentVector = new DynamicMatrix<double>(1, 1);
    AdmittanceMatrix = new DynamicMatrix<double>(1, 1);
    nodeArray = new DynamicArray<int>(5);
}

InputReader::~InputReader() {
    delete CurrentVector;
    delete AdmittanceMatrix;
    delete nodeArray;
}

void InputReader::Read(const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        std::cout << "Error: File does not exist." << std::endl;
        exit(1);
    }

    std::ifstream file(filename);

    char ch;
    while (file.get(ch)) {
        switch (ch) {
            case 'R': {
                ResistorData& resistorData = readResistor(file);
                addToAdmMatrix(resistorData.NodeA, resistorData.NodeA, resistorData.Resistance);
                addToAdmMatrix(resistorData.NodeB, resistorData.NodeB, resistorData.Resistance);
                addToAdmMatrix(resistorData.NodeA, resistorData.NodeB, -resistorData.Resistance);
                addToAdmMatrix(resistorData.NodeB, resistorData.NodeA, -resistorData.Resistance);
                nodeArray->Add(resistorData.NodeA);
                nodeArray->Add(resistorData.NodeB);
                delete &resistorData;
                break;
            }

            case 'S': {
                const SourceData& sourceData = readSource(file);
                CurrentVector->ResizeAndSet(0, sourceData.Node - 1, sourceData.Voltage);
                nodeArray->Add(sourceData.Node);
                delete &sourceData;
                break;
            }

            case '\n':
                line++;
                break;

            default:
                std::cout << "Error: Unexpected character '" << ch << "' at line " << line << std::endl;
                exit(1);
                break;
        }
    }
    file.close();

    for (int y = 0; y < AdmittanceMatrix->GetLengthY(); y++) {
        if (CurrentVector->TryGet(0,y) == 0) {
            CurrentVector->ResizeAndSet(0,y,0);
        }
    }

    checkNodeIndexes();
    if (CurrentVector->GetLengthY() > AdmittanceMatrix->GetLengthY()) {
        std::cout << "Error: Some sources are not connected to any resistors." << std::endl;
        exit(1);
    }

}

InputReader::ResistorData & InputReader::readResistor(std::ifstream &file) {
    ResistorData& resistor = *new ResistorData();
    consume(file, ' ');
    resistor.NodeA = parseInt(file);
    consume(file, ' ');
    resistor.NodeB = parseInt(file);
    consume(file, ' ');
    resistor.Resistance = parseDouble(file);

    if (resistor.NodeA <= 0 || resistor.NodeB <= 0) {
        std::cout << "Error: Node index should be >= 0. At line " << line << std::endl;
        exit(1);
    }

    if (resistor.Resistance <= 0) {
        std::cout << "Error: Resistance has to be > 0. At line " << line << std::endl;
        exit(1);
    }

    return resistor;
}

InputReader::SourceData & InputReader::readSource(std::ifstream &file) {
    SourceData& source = *new SourceData();
    consume(file, ' ');
    source.Node = parseInt(file);
    consume(file, ' ');
    source.Voltage = parseDouble(file);

    if (source.Node <= 0) {
        std::cout << "Error: Node index should be >= 0. At line " << line << std::endl;
        exit(1);
    }

    return source;
}

int InputReader::parseInt(std::ifstream &file) {
    if (!isDigit(file.peek())) {
        std::cout << "Error: Expected digit in line " << line << std::endl;
        exit(1);
    }

    int returnVal = 0;

    char ch;
    while (isDigit(file.peek())) {
        file.get(ch);
        returnVal *= 10;
        returnVal += (ch - '0');
    }

    return returnVal;
}

double InputReader::parseFraction(std::ifstream &file) {
    if (!isDigit(file.peek())) {
        std::cout << "Error: Expected digit after dot in line " << line << std::endl;
        exit(1);
    }

    double returnVal = 0;
    int power = 1;

    char ch;
    while (isDigit(file.peek())) {
        file.get(ch);
        returnVal += ((ch - '0') / std::pow(10,power));
        power++;
    }

    return returnVal;
}

double InputReader::parseDouble(std::ifstream &file) {
    double mainPart = parseInt(file);

    if (file.peek() == '.') {
        file.get();
        double fractionPart = parseFraction(file);
        mainPart += fractionPart;
    }

    return mainPart;
}

void InputReader::consume(std::ifstream &file, char c) {
    if (file.peek() == c) {
        file.get();
    } else {
        std::cout << "Error: Expected char '" << c << "' in line " << line << std::endl;
        exit(1);
    }
}

bool InputReader::isDigit(const char c)
{
    return c >= '0' && c <= '9';
}

bool InputReader::isAlpha(const char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

void InputReader::addToAdmMatrix(int x, int y, double resistance) const {
    AdmittanceMatrix->ResizeAndSet(x-1, y-1, AdmittanceMatrix->TryGet(x-1, y-1) + (1/resistance));
}

void InputReader::checkNodeIndexes() const {
    for (int i = 0; i < nodeArray->Length-1; i++) {
        for (int j = 0; j < nodeArray->Length-1; j++) {
            if (nodeArray->Get(j) > nodeArray->Get(j+1)) {
                int old = nodeArray->Get(j+1);
                nodeArray->Set(j+1, nodeArray->Get(j));
                nodeArray->Set(j, old);
            }
        }
    }

    int currentMax = 0;
    for (int i = 0; i < nodeArray->Length; i++) {
        if (nodeArray->Get(i) != currentMax && nodeArray->Get(i) != currentMax+1) {
            std::cout << "Error: There is a node with an index of " << nodeArray->Get(i) << ", but there is no node with an index of "  << currentMax+1 << std::endl;
            exit(1);
        }
        currentMax = nodeArray->Get(i);
    }
}

