cmake_minimum_required(VERSION 2.6)

project(mask C CXX)

#set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -Wno-unused-parameter")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/third_party/lib/cmake")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/third_party")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

message(STATUS "CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")
message(STATUS "EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH}")

# find muduo libraries
find_package(Muduo REQUIRED)
message(STATUS "MUDUO_INCLUDE_DIRS ${MUDUO_INCLUDE_DIRS}")
message(STATUS "MUDUO_BASE_LIBRARIES ${MUDUO_BASE_LIBRARIES}")
message(STATUS "MUDUO_NET_LIBRARIES ${MUDUO_NET_LIBRARIES}")

# find http-parser libraries
find_package(HttpParser REQUIRED)
message(STATUS "HTTP_PARSER_INCLUDE_DIRS ${HTTP_PARSER_INCLUDE_DIRS}")
message(STATUS "HTTP_PARSER_LIBRARIES ${HTTP_PARSER_LIBRARIES}")

# find rapidjson
find_package(RapidJSON REQUIRED)
message(STATUS "RAPIDJSON_INCLUDE_DIRS ${RAPIDJSON_INCLUDE_DIRS}")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/third_party/include)

add_subdirectory(mask)
