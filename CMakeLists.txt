cmake_minimum_required(VERSION 3.14)
project(sort_binary_file)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(${PROJECT_NAME} main.cpp BinFileGenerator.h BinFileGenerator.cpp BinFileGeneratorTest.cpp MergeSort.h MergeSort.cpp BinFileSortTest.cpp QuickSort.h QuickSortTest.cpp CombinedSort.h CombinedSort.cpp RadixSort.h RadixSort.cpp)

target_link_libraries(${PROJECT_NAME} gtest_main gtest pthread)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
