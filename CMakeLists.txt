cmake_minimum_required(VERSION 3.6)
project(Sniff)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp grap_80211.cpp grap_80211.h)
add_executable(Sniff ${SOURCE_FILES})