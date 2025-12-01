#ifndef CURRENTANALYSIS_INPUTREADER_H
#define CURRENTANALYSIS_INPUTREADER_H
#include "Matrix.h"

class InputReader {
    DynamicMatrix<double>* AdmittanceMatrix = nullptr;
    DynamicMatrix<double>* VoltageVector = nullptr;

    InputReader();
    ~InputReader();

    static void Read(const std::string &filename);

private:
    typedef struct ResistorData {
        int NodeA = -1;
        int NodeB = -1;
        double Resistance = -1;
    } ResistorData;

    typedef struct SourceData {
        int Node = -1;
        double Voltage = -1;
    } SourceData;

    static ResistorData& readResistor(std::ifstream& file);

    static SourceData& readSource(std::ifstream& file);
    static int parseInt(std::ifstream& file);
    static double parseDouble(std::ifstream& file);
    static void consume(std::ifstream& file, char c);
    static bool isDigit(char c);
    static bool isAlpha(char c);
};


#endif //CURRENTANALYSIS_INPUTREADER_H