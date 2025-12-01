#ifndef CURRENTANALYSIS_INPUTREADER_H
#define CURRENTANALYSIS_INPUTREADER_H
#include "Matrix.h"

class InputReader {
    typedef struct ResistorData {
        int NodeA = -1;
        int NodeB = -1;
        double Resistance = -1;
    } ResistorData;

    typedef struct SourceData {
        int Node = -1;
        double Voltage = -1;
    } SourceData;

    ResistorData& readResistor(std::ifstream& file);
    SourceData& readSource(std::ifstream& file);
    static int parseInt(std::ifstream& file);
    static double parseDouble(std::ifstream& file);
    static void consume(std::ifstream& file, char c);
    static inline bool isDigit(char c);
    static inline bool isAlpha(char c);
    inline void addToAdmMatrix(int x, int y, double value) const;



public:
    DynamicMatrix<double>* AdmittanceMatrix = nullptr;
    DynamicMatrix<double>* VoltageVector = nullptr;

    InputReader();
    ~InputReader();

    void Read(const std::string &filename);
};


#endif //CURRENTANALYSIS_INPUTREADER_H