cmake_minimum_required(VERSION 3.24)
project(Day_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(Day_01 main.cpp RawData/RawData.cpp RawData/RawData.h RawData/RawData.cpp Models/MoveInstruction.cpp Models/MoveInstruction.h Models/Crane.cpp Models/Crane.h Logic/CraneHandler.cpp Logic/CraneHandler.h Logic/StringListHelpers.cpp Logic/StringListHelpers.h Logic/ConsoleHelpers.cpp Logic/ConsoleHelpers.h)
