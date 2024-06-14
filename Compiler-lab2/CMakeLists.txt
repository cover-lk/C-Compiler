cmake_minimum_required(VERSION 3.16)
project(Compilerlab2)
set(CMAKE_CXX_STANDARD 14)
# 使用 cmake 的 flex 模块
include(FindFLEX)
if(FLEX_FOUND)
 message("Info: flex found!")
else()
 message("Error: flex not found!")
endif()
# 为了 flex 新增头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR})
# 指定 flex 编译目标
FLEX_TARGET(MyScanner lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_compile_options(-pedantic)
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
add_executable(Compilerlab2
 main.cpp
 keyword.cpp
 scanner.cpp
 output.cpp
 ${FLEX_MyScanner_OUTPUTS}
)
target_compile_features(Compilerlab2 PRIVATE cxx_std_14)
