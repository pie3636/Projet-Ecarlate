#include <cassert>
#include "BollingerBands.h"

BollingerBands::BollingerBands() : BollingerBands(20, 2.0) {}

BollingerBands::BollingerBands(unsigned _MALength, float _width) : MALength(_MALength), width(_width) {
    assert(width > 0);
}

std::vector <std::vector <double>> BollingerBands::applyTo(const std::vector <struct Candle> candles) {
    std::vector <std::vector <double>> values;
    float oldMA, MA = 0, partialStdDev = 0;
    std::vector <float> pastMA;
    int closeIndex = 0;

    const unsigned offset = MALength;
    for (unsigned i = 0; i < offset; i++) {
        pastMA.push_back(MA);
        oldMA = MA;
        MA += candles[i].close / MALength;
        partialStdDev += (candles[i].close - oldMA) * (candles[i].close - MA);
        values.push_back({0, 0});
    }

    values.push_back({MA - width * MALength * partialStdDev / (MALength - 1),
                      MA + width * MALength * partialStdDev / (MALength - 1)});

    for (unsigned i = offset; i < candles.size(); i++) {
        oldMA = MA;
        MA += (candles[i].close - candles[i - MALength].close) / MALength;
        partialStdDev += (candles[i].close - oldMA) * (candles[i].close - MA) -
                         (candles[i - MALength].close - pastMA[closeIndex] - candles[i - MALength].close / MALength) *
                         (candles[i - MALength].close - pastMA[closeIndex]);
        closeIndex = (closeIndex + 1) % MALength;
        values.push_back({MA - width * MALength * partialStdDev / (MALength - 1),
                          MA + width * MALength * partialStdDev / (MALength - 1)});
    }

    return values;
}