cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME Oware)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fno-omit-frame-pointer -fno-exceptions -fsanitize=address")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/Oware.cpp
    ${CMAKE_SOURCE_DIR}/src/GameState.cpp
    ${CMAKE_SOURCE_DIR}/src/GameLogic.cpp
)

add_executable(${PROJECT_NAME} 
    ${SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
)

add_executable(test_${PROJECT_NAME}
    ${SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/test/test.cpp
)
target_include_directories(test_${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/test/
)

add_executable(benchmark_${PROJECT_NAME}
    ${SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/benchmark/benchmark.cpp
    ${CMAKE_SOURCE_DIR}/benchmark/Watch.cpp
)
target_include_directories(benchmark_${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/benchmark
)
