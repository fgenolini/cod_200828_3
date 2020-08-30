cmake_minimum_required(VERSION 3.16)

set(APP_LOW_NAME task3)

# Performance improved sort and search in C / C++
project(${APP_LOW_NAME} VERSION 0.0.1)

include(CTest)
enable_testing()

# C++ standard required = C++ 20 (for span)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CommonSourcesList
  large_arrays.cpp
  randomise_input.cpp
  )

add_executable(${APP_LOW_NAME} ${APP_LOW_NAME}.cpp ${CommonSourcesList})

target_compile_options(${APP_LOW_NAME} PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall -Wextra>
  $<$<CXX_COMPILER_ID:MSVC>:/Wall /w45038 /wd4365 /wd4626 /wd4820>)

add_test(${APP_LOW_NAME} ${APP_LOW_NAME})
