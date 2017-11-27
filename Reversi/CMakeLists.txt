cmake_minimum_required(VERSION 3.8)
project(Reversi)

add_subdirectory(lib/googletest-master)

include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES src/main.cpp include/Board.h include/Game.h include/Player.h include/PlayGround.h include/Reversi.h include/ReversiPlayer.h src/Board.cpp src/Player.cpp src/PlayGround.cpp src/Reversi.cpp src/ReversiPlayer.cpp tests/gtest_main.cpp tests/test_Board.cpp tests/test_ReversiPlayer.cpp tests/test_Player.cpp tests/test_Reversi.cpp)
add_executable(Reversi ${SOURCE_FILES})

target_link_libraries(Reversi gtest gtest_main)
