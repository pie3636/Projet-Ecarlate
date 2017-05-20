#ifndef INDICATORS_MACD_H
#define INDICATORS_MACD_H

#include "../Indicator.h"

class MACD : public Indicator {
    public:
        MACD();
        MACD(unsigned _shortEMALength, unsigned _longEMALength, unsigned _signalLength);
        std::vector <std::vector <double>> applyTo(const std::vector <struct Candle> candles);

    private:
        unsigned shortEMALength, longEMALength, signalLength;
};

#endif //INDICATORS_MACD_H
