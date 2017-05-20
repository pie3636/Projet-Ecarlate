#ifndef INDICATORS_BOLLINGERBANDS_H
#define INDICATORS_BOLLINGERBANDS_H

#include <vector>
#include "../Indicator.h"

class BollingerBands : public Indicator {
    public:
        BollingerBands();
        BollingerBands(unsigned _MALength, float _width);
        std::vector <std::vector <double>> applyTo(const std::vector <struct Candle> candles);

    private:
        unsigned MALength;
        float width;
};

#endif // INDICATORS_BOLLINGERBANDS_H
