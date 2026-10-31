cmake_minimum_required(VERSION 3.10)

project(AdaptiveNetworkTrafficController)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(include)

# Build executable from multiple source files
add_executable(controller
    src/main.cpp
    src/Server.cpp
    src/RoutingEngine.cpp
)