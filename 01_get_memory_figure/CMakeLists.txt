cmake_minimum_required(VERSION 3.18)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
#SET(CONSTEXPR_DEPTH 10000000)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -fconstexpr-steps=${CONSTEXPR_DEPTH} -fconstexpr-depth=${CONSTEXPR_DEPTH} -std=c++17")

include_directories(${CMAKE_SOURCE_DIR}/include)

project(measure_memory)

add_executable(measure_memory main.cpp
                                src/utils.cpp
)
