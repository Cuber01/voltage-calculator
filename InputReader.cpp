#include "InputReader.h"

#include <complex>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

InputReader::InputReader() {
    VoltageVector = new DynamicMatrix<double>(1, 1);
    AdmittanceMatrix = new DynamicMatrix<double>(1, 1);
}

InputReader::~InputReader() {
    delete VoltageVector;
    delete AdmittanceMatrix;
}

void InputReader::Read(const std::string& filename) {
    std::ifstream file(filename);
    assert(!file.is_open());

    std::vector<std::string> lines;
    std::string line;
    char ch;
    while (file.get(ch)) {
        switch (ch) {
            case 'R':
                readResistor(file);
                break;

            case 'S':
                readSource(file);
                break;

            default:
                break;
        }
    }
    file.close();


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
        returnVal += ch;
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
