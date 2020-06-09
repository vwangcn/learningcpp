cmake_minimum_required(VERSION 3.13)
project(main)

set(CMAKE_CXX_STANDARD 14)

set(SFML_ROOT C:/sfml2.5)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${SFML_ROOT}/include
)
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        ${SFML_ROOT}/lib
)
add_executable(main main.cpp utils.cpp trigger.cpp feedparser.cpp newsstory.cpp)

include_directories(${SFML_ROOT/include})
target_link_libraries(main sfml-network sfml-system)
