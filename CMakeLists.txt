cmake_minimum_required(VERSION 3.19)
project(SPLFlix)

set(CMAKE_CXX_STANDARD 14)


add_executable(SPLFlix main.cpp Session.cpp Session.h Watchable.cpp Watchable.h Action.cpp Action.h User.cpp User.h json.hpp)