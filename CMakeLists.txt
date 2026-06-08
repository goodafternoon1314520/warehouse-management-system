cmake_minimum_required(VERSION 3.10)

project(warehouse_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 第三方库
# ==========================================

find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)

# ==========================================
# 头文件目录
# ==========================================

include_directories(
        include
        generated
        ${Protobuf_INCLUDE_DIRS}
)

# ==========================================
# Protobuf库
# ==========================================

add_library(
        warehouse_proto
        generated/proto/warehouse.pb.cc
)

target_link_libraries(
        warehouse_proto
        PUBLIC
        ${Protobuf_LIBRARIES}
)

# ==========================================
# 公共源码
# ==========================================

set(COMMON_SRCS
        src/ThreadPool.cpp
        src/TokenManager.cpp
        src/Crypto.cpp
        src/RSAUtil.cpp
        src/RSAManager.cpp
        src/MessageFramer.cpp
        src/SecureChannel.cpp
)

# ==========================================
# Server
# ==========================================

add_executable(
        server
        server/server.cpp
        ${COMMON_SRCS}
)

target_link_libraries(
        server
        PRIVATE
        warehouse_proto
        SQLite::SQLite3
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ==========================================
# Client
# ==========================================

add_executable(
        client
        client/client.cpp
        src/Crypto.cpp
        src/RSAUtil.cpp
        src/RSAManager.cpp
        src/MessageFramer.cpp
        src/SecureChannel.cpp
)

target_link_libraries(
        client
        PRIVATE
        warehouse_proto
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ==========================================
# Protobuf Test
# ==========================================

add_executable(
        proto_test
        tests/protobuf_test.cpp
)

target_link_libraries(
        proto_test
        PRIVATE
        warehouse_proto
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ==========================================
# Crypto Test
# ==========================================

add_executable(
        crypto_test
        tests/crypto_test.cpp
        src/Crypto.cpp
        src/RSAUtil.cpp
)

target_link_libraries(
        crypto_test
        PRIVATE
        warehouse_proto
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ==========================================
# RSA Key Generate Test
# ==========================================

add_executable(
        rsa_test
        tests/rsa_test.cpp
        src/RSAUtil.cpp
        src/RSAManager.cpp
)

target_link_libraries(
        rsa_test
        PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ==========================================
# RSA Encrypt Decrypt Test
# ==========================================

add_executable(
        rsa_enc_dec_test
        tests/rsa_enc_dec_test.cpp
        src/RSAUtil.cpp
        src/RSAManager.cpp
)

target_link_libraries(
        rsa_enc_dec_test
        PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ==========================================
# 输出信息
# ==========================================

message(STATUS "====================================")
message(STATUS "Protobuf Include: ${Protobuf_INCLUDE_DIRS}")
message(STATUS "Protobuf Libraries: ${Protobuf_LIBRARIES}")
message(STATUS "SQLite3 Found")
message(STATUS "OpenSSL Found")
message(STATUS "====================================")