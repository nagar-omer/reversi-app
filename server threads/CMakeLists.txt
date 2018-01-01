cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Server.cpp Server.h Game.h StartCommand.h Command.h CommandsManager.cpp CommandsManager.h GameManager.cpp GameManager.h ListCommand.h JoinCommand.h CloseCommand.h PlayCommand.h)
add_executable(Server ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS -pthread)