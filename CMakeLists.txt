cmake_minimum_required(VERSION 3.0.0)
project(8EMU 0.1.0)

include(CTest)
enable_testing()

add_library(cc cc.cpp)

set(CPACK_8EMU ${8EMU})
set(CPACK_1.0 ${1.0})
include(CPack)
