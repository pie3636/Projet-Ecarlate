#include <sstream>
#include <iostream>
#include "Options.h"

Options::Options(std::string _inputFile, std::string _outputFile, long _candleWidth,
                 std::vector <Indicator *> &_indicators)
        : inputFile(_inputFile), outputFile(_outputFile), candleWidth(_candleWidth), indicators(_indicators),
          isExited(false) {}

void Options::parseFromArguments(int argc, char **argv) {
    std::vector <std::string> args;
    for (int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }
    for (int i = 1; i < argc; i++) {
        if ((args[i] == "-i" || args[i] == "--input") && i + 1 < argc) {
            inputFile = argv[++i];
            continue;
        }
        if ((args[i] == "-o" || args[i] == "--output") && i + 1 < argc) {
            outputFile = argv[++i];
            continue;
        }
        if ((args[i] == "-t" || args[i] == "--timeframe") && i + 1 < argc) {
            candleWidth = std::stol(argv[++i]);
            continue;
        }
        if (args[i] == "-h" || args[i] == "--help") {
            isExited = true;
        }
        // TODO Indicators
        if (isExited) {
            std::cout << "Arguments:" << std::endl
                      << "-i, --input       Input file. Must contain CSV data formatted as [timestamp, volume, price]"
                      << std::endl
                      << "-o, --output      Output file. Formatted as CSV data" << std::endl
                      << "-t, --timeframe   Candle width in minutes" << std::endl
                      << "-h, --help        Display this help message and exits" << std::endl;
        }
    }
}

std::string Options::getInputFile(void) const {
    return inputFile;
}

std::string Options::getOutputFile(void) const {
    return outputFile;
}

long Options::getCandleWidth(void) const {
    return candleWidth;
}

const std::vector <Indicator *> &Options::getIndicators(void) const {
    return indicators;
}

bool Options::exited(void) const {
    return false;
}
