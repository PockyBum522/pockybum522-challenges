cmake_minimum_required(VERSION 3.24)
project(Day_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(Day_01 main.cpp RawData/RawData.cpp RawData/RawData.h RawData/RawData.cpp Logic/StringListHelpers.cpp Logic/StringListHelpers.h Logic/ListProcessor.cpp Logic/ListProcessor.h Logic/RawDataLoader.cpp Logic/RawDataLoader.h Logic/CharListHelpers.h Logic/CharListHelpers.cpp)
