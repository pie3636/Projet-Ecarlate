cmake_minimum_required(VERSION 3.6)
project(Indicators)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp HistoricalData.cpp HistoricalData.h Indicator.h indicators/MACD.cpp indicators/MACD.h indicators/BollingerBands.cpp indicators/BollingerBands.h HistoricalData.cpp HistoricalData.h Indicator.h Options.cpp Options.h Candle.h)
add_executable(Indicators ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -pg -g -Wall -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wzero-as-null-pointer-constant -Wmain -pedantic -Wfatal-errors -Wextra")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x -Wall -fomit-frame-pointer -fexpensive-optimizations -O3")