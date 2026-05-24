# 仓库管理系统（Warehouse Management System）

一个基于 Linux + C++ 开发的终端仓库管理系统。

## 项目介绍

本项目是一个使用 C++ 开发的仓库管理系统，运行于 Linux 环境，采用面向对象设计，实现商品管理、库存管理、文件存储等功能。

项目主要用于：

- 学习 Linux 下 C++ 项目开发
- 熟悉面向对象编程
- 掌握文件持久化
- 学习 Git/GitHub 工程管理
- 练习 CMake 工程构建

---

## 功能列表

### 当前功能

- [x] 商品添加
- [x] 商品显示
- [x] 菜单系统
- [x] CMake 构建
- [x] GitHub 工程管理

### 后续计划

- [ ] 商品删除
- [ ] 商品修改
- [ ] 商品查询
- [ ] 文件持久化
- [ ] 用户登录系统
- [ ] 权限管理
- [ ] 入库管理
- [ ] 出库管理
- [ ] 日志系统
- [ ] SQLite 数据库支持
- [ ] Qt 图形界面

---

## 项目结构

```text
warehouse_system/
├── include/           # 头文件
│   └── Product.h
│
├── src/               # 源文件
│   ├── main.cpp
│   └── Product.cpp
│
├── data/              # 数据文件
│
├── build/             # CMake 编译目录
│
├── CMakeLists.txt     # CMake 配置
│
├── .gitignore
│
└── README.md
```

---

## 开发环境

| 工具 | 版本 |
|------|------|
| OS | Ubuntu / Linux |
| 编译器 | g++ |
| C++ 标准 | C++17 |
| 构建工具 | CMake |
| 版本管理 | Git |

---

## 编译方法

### 1. 克隆项目

```bash
git clone https://github.com/你的用户名/warehouse-management-system.git
```

### 2. 进入项目目录

```bash
cd warehouse-management-system
```

### 3. 创建 build 目录

```bash
mkdir build
cd build
```

### 4. 使用 CMake 编译

```bash
cmake ..
make
```

---

## 运行项目

在 build 目录下执行：

```bash
./warehouse
```

---

## 项目截图

后续补充。

---

## 核心技术

### 1. 面向对象设计

项目采用类封装设计：

- Product 商品类
- Warehouse 仓库类
- User 用户类

---

### 2. STL 容器

使用：

```cpp
vector<Product>
```

管理商品数据。

---

### 3. 文件存储

后续将实现：

- 商品数据保存
- 自动读取库存
- 日志持久化

---

### 4. Linux 工程化

项目采用：

- CMake
- Git
- 多目录结构
- 模块化开发

---

## Git 提交规范

推荐提交信息：

```text
Add product management
Implement file storage
Refactor warehouse class
Add login system
```

---

## 后续升级方向

### SQLite 数据库

实现真正数据库管理。

### Qt 图形界面

实现 GUI 仓库系统。

### Socket 网络通信

实现客户端/服务器仓库系统。

### 多线程

实现并发库存管理。

---

## 作者

作者：你的名字

---

## License

MIT License

