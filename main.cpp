#include <iostream>
#include "HistoricalData.h"

int main(int argc, char *argv[]) {
    std::vector <Indicator *> indicators = {
            // new MACD(12, 26, 9), // TODO Check
            // new BollingerBands(20, 2) // TODO Check
    };
    Options options("../.bitstampUSD.csv", "../output.csv", 15 * 60, indicators);
    options.parseFromArguments(argc, argv);
    if (options.exited()) {
        return EXIT_SUCCESS;
    }
    std::cout << "Reading file [" << options.getInputFile() << "]..." << std::endl;
    HistoricalData historicalData(options);
    // Shape of candles, shadow, ratio body, etc, multi candle patterns
    // Trend?, wedges, patterns, waves, divergences etc
    // Fibonacci
    // Supports/Resistances
    // Orders
    // EMA
    // SMA
    // MA 10 20 50 100 200
    // Parabolic SAR
    // Stochastic RSI
    // RSI
    // ADX
    // SMA 7 20 65
    // Ichimoku
    // Pivots
    // https://www.tradingtechnologies.com/help/x-study/technical-indicator-definitions/list-of-technical-indicators/
    std::cout << "Applying indicators..." << std::endl;
    historicalData.applyIndicators();
    std::cout << "Writing to file [" << options.getOutputFile() << "]..." << std::endl;
    historicalData.writeToFile();
    return EXIT_SUCCESS;
}