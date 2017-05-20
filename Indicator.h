#ifndef INDICATOR_H
#define INDICATOR_H

#include <vector>
#include "Candle.h"

class Indicator {
    public:
        virtual ~Indicator() {};
        virtual const std::vector <std::vector <double>> applyTo(const std::vector <struct Candle> candles) const = 0;
};

#endif // INDICATOR_H
