cmake_minimum_required(VERSION 3.16)
project(hangman VERSION 0.1.0)

include(cmake/prelude.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt REQUIRED)
find_package(CLI11 REQUIRED)

include(cmake/fetched-libs.cmake)

add_executable(main source/main.cpp)
target_include_directories(main PRIVATE source)
target_link_libraries(main PRIVATE fmt::fmt CLI11::CLI11 fetch::linr)
target_compile_options(main PRIVATE -Wall -Wextra -Wconversion)

# sanitizer
if(CMAKE_BUILD_TYPE EQUAL Debug)
  target_compile_options(main PRIVATE -fsanitize=address,leak,undefined)
  target_link_options(main PRIVATE -fsanitize=address,leak,undefined)
endif()
