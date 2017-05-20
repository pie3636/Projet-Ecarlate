#ifndef CANDLE_H
#define CANDLE_H

struct Candle {
    long startTime;
    float open;
    float high;
    float low;
    float close;
    float volume;
    /*
     * Positive volume: volume that led to a price increase
     * Negative volume: volume that led to a price decrease
     * Zero volume: volume that didn't lead to a price chance
     */
    float volumeGE0; // >= 0
    float volumeGT0; // > 0
    float volumeLE0; // <= 0
    float volumeLT0; // < 0
    float volumeEQ0; // == 0
    float volumeNE0; // != 0
    float tradeCount;
    float avgPrice;
    float avgWeightedPrice;
};

#endif // CANDLE_H
