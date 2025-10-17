# 需求的最低cmake版本
cmake_minimum_required(VERSION 3.12)

# 工程名
project(avlTree)

# 支持的C++版本
set(CMAKE_CXX_STANDARD 17)

# 编译优化
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")

# 本工程所有cpp文件编译链接
add_executable(avlTree "main.cpp" "AVLTree.h" "AVLTree.impl.h" "BST.h" "BST.impl.h" "StdAVLTree.h" "StdAVLTree.impl.h")