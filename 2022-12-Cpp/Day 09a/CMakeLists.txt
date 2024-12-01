cmake_minimum_required(VERSION 3.24)
project(Day_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(Day_01 main.cpp RawData/RawData.cpp RawData/RawData.h RawData/RawData.cpp Logic/ListHelpers/StringListHelpers.cpp Logic/ListHelpers/StringListHelpers.h Logic/ListProcessor.cpp Logic/ListProcessor.h RawData/RawDataLoader/RawDataLoader.cpp RawData/RawDataLoader/RawDataLoader.h Logic/ListHelpers/CharListHelpers.h Logic/ListHelpers/CharListHelpers.cpp LoggerConsole/LoggerConsole.cpp LoggerConsole/LoggerConsole.h Models/BoardSquare.cpp Models/BoardSquare.h Models/Rope.cpp Models/Rope.h Models/Board.cpp Models/Board.h)
