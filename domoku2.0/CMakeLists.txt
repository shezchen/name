cmake_minimum_required(VERSION 3.29)
project(domoku2_0 C)

set(CMAKE_C_STANDARD 23
CMAKE_C_FLAGS_RELEASE -ofast)

add_executable(domoku2_0  bot.h main.c)
