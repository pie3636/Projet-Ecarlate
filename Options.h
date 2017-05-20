#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>
#include "Indicator.h"

class Options {
    private:
        std::string inputFile;
        std::string outputFile;
        long candleWidth; // In seconds
        std::vector <Indicator *> indicators;
        bool isExited;
    public:
        Options(std::string _inputFile, std::string _outputFile, long _candleWidth,
                std::vector <Indicator *> &_indicators);
        void parseFromArguments(int argc, char *argv[]);
        bool exited(void) const;
        std::string getInputFile(void) const;
        std::string getOutputFile(void) const;
        long getCandleWidth(void) const;
        const std::vector <Indicator *> &getIndicators(void) const;
};

#endif // OPTIONS_H
