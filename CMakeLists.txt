cmake_minimum_required(VERSION 3.10)

project(warehouse_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================
# 第三方库
# ========================

# Protobuf
find_package(Protobuf REQUIRED)

# Threads
find_package(Threads REQUIRED)

# SQLite
find_package(SQLite3 REQUIRED)

# OpenSSL
find_package(OpenSSL REQUIRED)

# ========================
# include 目录
# ========================
include_directories(
        include
        ${Protobuf_INCLUDE_DIRS}
)

# ========================
# protobuf 生成文件
# ========================
set(PROTO_SRCS
        generated/proto/warehouse.pb.cc
)

set(PROTO_HDRS
        generated/proto/warehouse.pb.h
)

# ========================
# 项目源文件
# ========================
set(SOURCES

        src/server.cpp
        src/client.cpp

        src/ThreadPool.cpp
        src/TokenManager.cpp

        ${PROTO_SRCS}
)

# ========================
# server 可执行文件
# ========================
add_executable(server
        src/server.cpp
        src/ThreadPool.cpp
        src/TokenManager.cpp
        generated/proto/warehouse.pb.cc
        src/Crypto.cpp
        src/RSAUtil.cpp
        src/MessageFramer.cpp
)

target_link_libraries(server
        ${Protobuf_LIBRARIES}
        SQLite::SQLite3
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ========================
# client 可执行文件
# ========================
add_executable(client
        src/client.cpp
        src/MessageFramer.cpp

        src/Crypto.cpp
        src/RSAUtil.cpp

        generated/proto/warehouse.pb.cc
)

target_link_libraries(client
        ${Protobuf_LIBRARIES}
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ========================
# protobuf 测试程序（可选）
# ========================
add_executable(proto_test
        src/protobuf_test.cpp

        src/Crypto.cpp
        src/RSAUtil.cpp

        generated/proto/warehouse.pb.cc
)

target_link_libraries(proto_test
        ${Protobuf_LIBRARIES}
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ========================
# Crypto 测试程序
# ========================
add_executable(crypto_test
        src/crypto_test.cpp
        generated/proto/warehouse.pb.cc
        src/Crypto.cpp
        src/RSAUtil.cpp
)

target_link_libraries(crypto_test
        ${Protobuf_LIBRARIES}
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ========================
# RSA 测试程序
# ========================
add_executable(rsa_test
        src/rsa_test.cpp
        src/RSAUtil.cpp
)

target_link_libraries(rsa_test
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ========================
# 编译信息输出
# ========================
message(STATUS "Protobuf include: ${Protobuf_INCLUDE_DIRS}")
message(STATUS "Protobuf libs: ${Protobuf_LIBRARIES}")