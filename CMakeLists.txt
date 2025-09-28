# 需求的最低cmake版本
cmake_minimum_required(VERSION 3.12)

# 工程名
project(avlTree)

# 支持的C++版本
set(CMAKE_CXX_STANDARD 17)

# 本工程所有cpp文件编译链接
add_executable(avlTree "main.cpp" "AVLTree.h" "AVLTree.cpp")