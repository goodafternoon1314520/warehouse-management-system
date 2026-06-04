# Warehouse Management System

基于 Linux + C++17 开发的企业级仓库管理系统（WMS）。

## 项目简介

Warehouse Management System（WMS）是一个采用现代 C++ 技术栈实现的仓库管理系统。

项目采用客户端/服务端架构，支持：

* 用户登录认证
* Token 会话管理
* 库存管理
* 入库管理
* 出库管理
* 库存盘点
* 盘点差异过账
* SQLite 数据存储
* Protobuf 高效数据传输
* AES-256-GCM 安全通信
* 多线程并发处理

项目目标是模拟企业级 WMS 系统的核心业务流程，并实现安全可靠的跨平台通信架构。

---

## 技术栈

### 开发环境

* Ubuntu 24.04 LTS
* GCC 13+
* CMake 3.16+
* Git

### 核心技术

* C++17
* Socket
* Thread Pool
* SQLite3
* Protocol Buffers
* OpenSSL
* AES-256-GCM
* Token Authentication

---

## 项目架构

```text
Client
    │
    ▼
Protocol Buffers
    │
    ▼
AES-256-GCM
    │
    ▼
MessageFramer
    │
    ▼
TCP Socket
    │
    ▼
Server
    │
    ├── Authentication
    ├── Inventory Service
    ├── Stock In Service
    ├── Stock Out Service
    ├── Stocktaking Service
    └── Settlement Service
    │
    ▼
SQLite Database
```

---

## 目录结构

```text
WarehouseSystem
│
├── client
│   └── client.cpp
│
├── server
│   └── server.cpp
│
├── include
│   ├── Crypto.h
│   ├── MessageFramer.h
│   ├── TokenManager.h
│   ├── ThreadPool.h
│   └── InventoryManager.h
│
├── src
│   ├── Crypto.cpp
│   ├── MessageFramer.cpp
│   ├── TokenManager.cpp
│   ├── ThreadPool.cpp
│   └── InventoryManager.cpp
│
├── proto
│   └── warehouse.proto
│
├── generated
│   └── proto
│
├── database
│   └── warehouse.db
│
├── tests
│
├── docs
│
├── build
│
├── CMakeLists.txt
│
└── README.md
```

---

## 功能模块

### 用户认证

支持：

* 登录
* Token生成
* Token验证
* 会话管理

---

### 库存管理

支持：

* 商品新增
* 商品修改
* 商品删除
* 商品查询

---

### 入库管理

支持：

* 采购入库
* 入库记录查询

---

### 出库管理

支持：

* 销售出库
* 出库记录查询

---

### 库存盘点

支持：

* 盘点任务创建
* 实盘数量录入
* 差异统计

---

### 盘点差异过账

支持：

* 盘盈过账
* 盘亏过账
* 自动生成库存调整记录

---

## 网络协议

### 登录请求

```protobuf
message LoginRequest {
    string username = 1;
    string password = 2;
}
```

### 登录响应

```protobuf
message LoginResponse {
    bool success = 1;
    string token = 2;
    string message = 3;
}
```

### 安全消息

```protobuf
message SecureMessage {
    bytes iv = 1;
    bytes tag = 2;
    bytes cipher = 3;
}
```

---

## 安全设计

### MessageFramer

解决 TCP：

* 粘包
* 拆包

数据格式：

```text
+------------+
| Length(4B) |
+------------+
| Payload    |
+------------+
```

---

### AES-256-GCM

实现：

* 数据加密
* 数据完整性校验
* 防止中间人篡改

包含：

* IV
* CipherText
* Authentication Tag

---

## 构建项目

### 安装依赖

```bash
sudo apt update

sudo apt install \
build-essential \
cmake \
libsqlite3-dev \
protobuf-compiler \
libprotobuf-dev \
libssl-dev
```

---

### 编译

```bash
mkdir build

cd build

cmake ..

make -j$(nproc)
```

---

## 运行服务端

```bash
./server
```

输出：

```text
Multi-thread Server started...
```

---

## 运行客户端

```bash
./client
```

输出：

```text
success = 1
token = admin_xxxxx
message = login success
```

---

## 测试

### Protobuf测试

```bash
./protobuf_test
```

### AES-GCM测试

```bash
./crypto_test
```

---

## 开发路线

### 已完成

* [x] CMake项目搭建
* [x] SQLite集成
* [x] Token认证
* [x] 多线程服务器
* [x] Protobuf通信
* [x] MessageFramer封包
* [x] AES-256-GCM加密

### 开发中

* [ ] RSA密钥交换
* [ ] SecureSession
* [ ] 库存盘点
* [ ] 差异过账
* [ ] API接口测试

### 计划中

* [ ] REST API
* [ ] Docker部署
* [ ] Web管理后台
* [ ] Redis缓存
* [ ] MySQL支持

---

## License

MIT License

---

## Author

Developed with C++17 on Linux.
