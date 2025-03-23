cmake_minimum_required(VERSION 3.10)
project(WeatherApplication)

set(CMAKE_CXX_STANDARD 17)

# Set CMake to find vcpkg packages
set(CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows")

# Find nlohmann-json package
find_package(nlohmann_json CONFIG REQUIRED)

# Add executable and source files
add_executable(WeatherApplication WeatherApplication.cpp)

# Link nlohmann-json
target_link_libraries(WeatherApplication PRIVATE nlohmann_json::nlohmann_json)
