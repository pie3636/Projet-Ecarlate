#ifndef HISTORICALDATA_H
#define HISTORICALDATA_H

#include <string>
#include <vector>
#include "Options.h"

struct Tick {
    long timestamp;
    float price;
    float volume;
};

class HistoricalData {
    public:
        HistoricalData(const Options &_options);
        void applyIndicators(void);
        void writeToFile(void);

    private:
        std::vector <std::vector <std::vector <double>>> values;
        void generateCandles(const std::vector <Tick> &ticks);
        const Options &options;
        std::vector <Candle> candles;
};

#endif // HISTORICALDATA_H
