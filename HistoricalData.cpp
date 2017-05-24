#include <fstream>
#include <sstream>
#include <iostream>
#include "HistoricalData.h"

HistoricalData::HistoricalData(const Options &_options) : values(), options(_options), candles() {
    std::vector <Tick> ticks;
    std::ifstream file(options.getInputFile());
    if (!file.is_open()) {
        throw new std::logic_error("File not open (HistoricalData/[ctor])");
    }
    std::string line;
    std::stringstream iss;
    Tick parsedTick;
    char comma;
    long lineCount = 0, totalLines = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            iss = std::stringstream(line);
            iss >> parsedTick.timestamp;
            iss >> comma;
            iss >> parsedTick.price;
            iss >> comma;
            iss >> parsedTick.volume;
            ticks.push_back(parsedTick);
        }
        lineCount++;
        if (lineCount == 100000) {
            lineCount = 0;
            totalLines += 100000;
            std::cout << totalLines << " lines processed." << std::endl;
        }
    }
    if (!ticks.empty()) {
        generateCandles(ticks);
    }
}

void HistoricalData::generateCandles(const std::vector <Tick> &ticks) {
    const long candleWidth = options.getCandleWidth();
    float lastPrice = 0, totalPrice = 0, totalWeightedPrice = 0;
    long curTimestamp = ticks[0].timestamp - ticks[0].timestamp % candleWidth - candleWidth;
    for (Tick tick: ticks) {
        while (tick.timestamp - curTimestamp >= candleWidth) {
            curTimestamp += candleWidth;
            if (!candles.empty()) {
#pragma GCC diagnostic ignored "-Wfloat-equal"
                candles.back().avgPrice = (candles.back().tradeCount == 0 ? candles.back().close : totalPrice / candles.back().tradeCount);
                candles.back().avgWeightedPrice = (candles.back().volumeNE0 == 0 ? candles.back().close : totalWeightedPrice / candles.back().volume);
#pragma GCC diagnostic pop
            }
            candles.push_back(
                    {curTimestamp, tick.price, tick.price, tick.price, tick.price, 0, 0, 0, 0, 0, 0, 0, 0, tick.price,
                     tick.price});
            totalPrice = totalWeightedPrice = 0;
        }
        Candle &lastCandle = candles.back();
        lastCandle.high = std::max(lastCandle.high, tick.price);
        lastCandle.low = std::min(lastCandle.low, tick.price);
        lastCandle.close = tick.price;
        lastCandle.volume += tick.volume;
        if (tick.price > lastPrice) lastCandle.volumeGT0 += tick.price;
        if (tick.price >= lastPrice) lastCandle.volumeGE0 += tick.price;
        if (tick.price < lastPrice) lastCandle.volumeLT0 += tick.price;
        if (tick.price <= lastPrice) lastCandle.volumeLE0 += tick.price;
#pragma GCC diagnostic ignored "-Wfloat-equal"
        if (tick.price == lastPrice) lastCandle.volumeEQ0 += tick.price;
        if (tick.price != lastPrice) lastCandle.volumeNE0 += tick.price;
#pragma GCC diagnostic pop
        lastPrice = tick.price;
        ++lastCandle.tradeCount;
        totalPrice += tick.price;
        totalWeightedPrice += tick.price * tick.volume;
        // TODO Volatility, EWMAVolatility
    }
}

void HistoricalData::applyIndicators(void) {
    for (Indicator *indicator: options.getIndicators()) {
        values.push_back(indicator->applyTo(candles));
    }
}

void HistoricalData::writeToFile(void) {
    std::ofstream file(options.getOutputFile());
    if (!file.is_open()) {
        throw new std::logic_error("File not open (HistoricalData/[~dtor])");
    }
    for (Candle candle: candles) {
        file << candle.startTime << ","
             << candle.open << ","
             << candle.high << ","
             << candle.low << ","
             << candle.close << ","
             << candle.volume << ","
             << candle.volumeGE0 << ","
             << candle.volumeGT0 << ","
             << candle.volumeLE0 << ","
             << candle.volumeLT0 << ","
             << candle.volumeEQ0 << ","
             << candle.volumeNE0 << ","
             << candle.tradeCount << ","
             << candle.avgPrice << ","
             << candle.avgWeightedPrice << std::endl;
    }
}
