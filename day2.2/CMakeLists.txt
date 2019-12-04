cmake_minimum_required (VERSION 2.6)
project (day2.2 LANGUAGES CXX)

set(BOOST_INCLUDE_DIRS /usr/include)


add_executable(day2.2 main.cpp)
target_include_directories(day2.2 PRIVATE ${BOOST_INCLUDE_DIRS})