cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(winkeys)
#
add_library(winkeysdll SHARED winkeysdll.cpp winkeysdll.h)
target_compile_definitions(winkeysdll PUBLIC -DWINKEYSDLL_EXPORTS)
target_compile_definitions(winkeysdll PUBLIC -DUNICODE -D_UNICODE)

add_executable(winkeys WIN32 main.cpp)
target_compile_definitions(winkeys PUBLIC -DUNICODE -D_UNICODE)
#target_link_libraries(winkeys winkeysdll)
