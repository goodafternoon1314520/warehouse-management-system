cmake_minimum_required(VERSION 3.10)

# 项目名称
project(WarehouseSystem)

# 使用 C++17
set(CMAKE_CXX_STANDARD 17)

# 头文件目录
include_directories(include)

# 源文件
set(SOURCES
    src/main.cpp
    src/Product.cpp
    src/Warehouse.cpp
)

# 生成可执行文件
add_executable(warehouse ${SOURCES})