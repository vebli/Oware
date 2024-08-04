cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME Oware)
project(${PROJECT_NAME})
# find_package(
#   SFML 2.5
#   COMPONENTS system window graphics
#   REQUIRED)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fno-omit-frame-pointer -fno-exceptions -fsanitize=address")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/game_state.cpp
    ${CMAKE_SOURCE_DIR}/src/game_logic.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
)

# target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics)
