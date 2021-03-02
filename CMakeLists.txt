cmake_minimum_required (VERSION 3.8)

project ("CppBinding" LANGUAGES CXX C)

set(CMAKE_BUILD_TYPE Release)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#target_compile_features(CppBinding PRIVATE cxx_std_17)

file(GLOB SOURCES "CppBinding/*.cpp" "CppBinding/*.hpp")

set(SOURCE_FILES CppBinding/export_functions.cpp CppBinding/BindingJava.cpp CppBinding/map.cpp)

add_library(CppBinding SHARED ${SOURCES})
