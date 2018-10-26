cmake_minimum_required(VERSION 3.12)
project(Game_of_Life)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES "Source Files/main.cpp" "Source Files/Application.cpp" "Header Files/Application.h" "Source Files/Random.cpp" "Header Files/Random.h" "Source Files/GameOfLife.cpp" "Header Files/GameOfLife.h")

add_executable(Game_of_Life ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Game_of_Life ${SFML_LIBRARIES})
endif()