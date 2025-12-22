cmake_minimum_required(VERSION 3.10)
project(BasalaevD_ExpressionAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем Google Test вручную (без add_subdirectory)
set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest)
set(GTEST_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${GTEST_INCLUDE_DIR})

# Компилируем Google Test как статическую библиотеку
add_library(gtest STATIC ${GTEST_SOURCE})

# Основной исполняемый файл тестов
add_executable(tests
    src/expressionanalyzer.cpp
    test/test_main.cpp
    test/test_tstack.cpp
    test/test_texpressionanalyzer.cpp
)

# Линкуем с gtest
target_link_libraries(tests gtest)