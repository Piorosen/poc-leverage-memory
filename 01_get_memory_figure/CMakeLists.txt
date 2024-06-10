cmake_minimum_required(VERSION 3.18)
project(measure_memory LANGUAGES C CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-fconstexpr-steps=${CONSTEXPR_DEPTH} -fconstexpr-depth=${CONSTEXPR_DEPTH}")

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(cxxopts CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(measure_memory main.cpp
                                src/utils.cpp
                                src/args.cpp
                                src/memory.cpp
)



target_link_libraries(measure_memory PRIVATE cxxopts::cxxopts)
target_link_libraries(measure_memory PRIVATE spdlog::spdlog)
