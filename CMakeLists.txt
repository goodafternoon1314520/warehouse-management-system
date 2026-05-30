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
    src/Logger.cpp
    src/User.cpp
    src/UserManager.cpp
    src/Utils.cpp
    src/Database.cpp
    src/TokenManager.cpp
    src/ThreadPool.cpp
)

# 生成可执行文件
add_executable(
        warehouse
        src/main.cpp
        ${SOURCES}
)

# 服务器
add_executable(
        server
        src/server.cpp
        src/TokenManager.cpp
        src/ThreadPool.cpp
)

# 客户端
add_executable(
        client
        src/client.cpp
)

find_package(SQLite3 REQUIRED)

target_link_libraries(
        warehouse
        SQLite::SQLite3
)