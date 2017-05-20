#include <cassert>
#include "MACD.h"

MACD::MACD() : MACD(12, 26, 9) {}

MACD::MACD(unsigned _shortEMALength, unsigned _longEMALength, unsigned _signalLength)
        : shortEMALength(_shortEMALength), longEMALength(_longEMALength), signalLength(_signalLength) {
    assert(longEMALength >= shortEMALength);
}

std::vector <std::vector <double>> MACD::applyTo(const std::vector <struct Candle> candles) {
    std::vector <std::vector <double>> values;
    const unsigned offset = longEMALength + signalLength - 1;
    float shortEMA = 0, longEMA = 0, signal = 0.0;

    for (unsigned i = 0; i < offset; i++) {
        shortEMA += (candles[i].close - shortEMA) * (2. / (shortEMALength + 1));
        longEMA += (candles[i].close - longEMA) * (2. / (longEMALength + 1));
        signal += (shortEMA - longEMA - signal) * (2. / (signalLength + 1));
        values.push_back({0});
    }

    values.push_back({signal});

    for (unsigned i = offset; i < candles.size(); i++) {
        shortEMA += (candles[i].close - shortEMA) * (2. / (shortEMALength + 1));
        longEMA += (candles[i].close - longEMA) * (2. / (longEMALength + 1));
        signal += (shortEMA - longEMA - signal) * (2. / (signalLength + 1));
        values.push_back({signal});
    }

    return values;
}