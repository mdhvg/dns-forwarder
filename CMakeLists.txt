cmake_minimum_required(VERSION 3.20.0)
project(dns)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# include_directories("${CMAKE_SOURCE_DIR}/deps/asio/asio/include")

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE MySource "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${MySource})