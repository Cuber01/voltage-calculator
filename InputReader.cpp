#include "InputReader.h"

#include <iostream>
#include <fstream>
#include <string>

InputReader::InputReader() {
    CurrentVector = new DynamicMatrix<double>(1, 1);
    AdmittanceMatrix = new DynamicMatrix<double>(1, 1);
}

InputReader::~InputReader() {
    delete CurrentVector;
    delete AdmittanceMatrix;
}

void InputReader::Read(const std::string& filename) {
    std::ifstream file(filename);
    assert(file.is_open());

    char ch;
    while (file.get(ch)) {
        switch (ch) {
            case 'R': {
                ResistorData& resistorData = readResistor(file);
                addToAdmMatrix(resistorData.NodeA, resistorData.NodeA, resistorData.Resistance);
                addToAdmMatrix(resistorData.NodeB, resistorData.NodeB, resistorData.Resistance);
                addToAdmMatrix(resistorData.NodeA, resistorData.NodeB, -resistorData.Resistance);
                addToAdmMatrix(resistorData.NodeB, resistorData.NodeA, -resistorData.Resistance);
                delete &resistorData;
                break;
            }

            case 'S': {
                const SourceData& sourceData = readSource(file);
                CurrentVector->ResizeAndSet(0, sourceData.Node - 1, sourceData.Voltage);
                delete &sourceData;
                break;
            }

            default:
                break;
        }
    }
    file.close();

    for (int y = 0; y < AdmittanceMatrix->GetLengthY(); y++) {
        if (CurrentVector->TryGet(0,y) == 0) {
            CurrentVector->ResizeAndSet(0,y,0);
        }
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
    return resistor;
}

InputReader::SourceData & InputReader::readSource(std::ifstream &file) {
    SourceData& source = *new SourceData();
    consume(file, ' ');
    source.Node = parseInt(file);
    consume(file, ' ');
    source.Voltage = parseDouble(file);
    return source;
}

int InputReader::parseInt(std::ifstream &file) {
    int returnVal = 0;

    char ch;
    while (isDigit(file.peek())) {
        file.get(ch);
        returnVal *= 10;
        returnVal += (ch - '0');
    }

    return returnVal;
}

double InputReader::parseDouble(std::ifstream &file) {
    double mainPart = parseInt(file);

    if (file.peek() == '.') {
        file.get();
        double decimalPart = parseInt(file);
        while (decimalPart > 0) {
            decimalPart /= 10;
        }
        mainPart += decimalPart;
    }

    return mainPart;
}

void InputReader::consume(std::ifstream &file, char c) {
    assert(file.peek() == c);
    if (file.peek() == c) {
        file.get();
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
