#ifndef CANDLE_H
#define CANDLE_H

struct Candle {
    long startTime;
    double high;
    double open;
    double low;
    double close;
    double volume;
    /*
     * Positive volume: volume that led to a price increase
     * Negative volume: volume that led to a price decrease
     * Zero volume: volume that didn't lead to a price chance
     */
    double volumeGE0; // >= 0
    double volumeGT0; // > 0
    double volumeLE0; // <= 0
    double volumeLT0; // < 0
    double volumeEQ0; // == 0
    double volumeNE0; // != 0
    double tradeCount;
    double avgPrice;
    double avgWeightedPrice;
};

#endif // CANDLE_H
