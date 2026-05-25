# 仓库管理系统（Warehouse Management System）

一个基于 Linux + C++17 开发的仓库管理系统。

项目采用面向对象设计（OOP）开发，实现了商品管理、库存管理、用户权限控制、日志系统、数据统计等功能，并使用 SQLite 数据库进行数据持久化。

该项目适用于：

- Linux C++ 学习
- 课程设计
- GitHub 项目展示
- 简历项目
- 面向对象实践
- SQLite 数据库实践

---

# 项目功能

## 用户系统

- 用户登录
- 管理员权限
- 员工权限
- 权限控制

---

## 商品管理

- 添加商品
- 删除商品
- 修改商品
- 查询商品
- 按名称搜索商品

---

## 库存管理

- 商品入库
- 商品出库
- 库存不足检测

---

## 数据统计

- 商品总数统计
- 仓库总价值统计
- 低库存预警

---

## 排序系统

- 按价格排序
- 按库存排序

---

## 日志系统

自动记录：

- 入库日志
- 出库日志
- 操作记录

---

## 数据持久化

- SQLite 数据库存储
- 文件自动加载
- SQL 数据查询

---

# 技术栈

## 开发环境

- Linux
- Ubuntu
- VSCode
- Git
- GitHub

---

## 编程语言

- C++17

---

## 使用技术

- STL
- 面向对象编程（OOP）
- 文件IO
- SQLite3
- CMake
- Git版本管理

---

# 项目结构

```text
warehouse_system/
├── include/
│   ├── Product.h
│   ├── Warehouse.h
│   ├── User.h
│   ├── UserManager.h
│   ├── Logger.h
│   ├── Utils.h
│   └── Database.h
│
├── src/
│   ├── main.cpp
│   ├── Product.cpp
│   ├── Warehouse.cpp
│   ├── User.cpp
│   ├── UserManager.cpp
│   ├── Logger.cpp
│   ├── Utils.cpp
│   └── Database.cpp
│
├── data/
│   ├── warehouse.db
│   ├── users.txt
│   └── logs.txt
│
├── build/
│
├── CMakeLists.txt
│
├── .gitignore
│
└── README.md
```

---

# 系统功能展示

## 登录系统

```text
===== Login =====
Username:
Password:
```

---

## 主菜单

```text
===== Warehouse System =====

1. Add Product
2. Show Products
3. Find Product
4. Delete Product
5. Update Product
6. Stock In
7. Stock Out
8. Save Data
9. Statistics
10. Sort By Price
11. Sort By Quantity
12. Search By Name
0. Exit
```

---

# 数据库设计

## products 表

```sql
CREATE TABLE products (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    quantity INTEGER,
    price REAL
);
```

---

# 默认用户

## 管理员

```text
Username: admin
Password: 123456
```

---

## 普通员工

```text
Username: staff
Password: 111111
```

---

# 编译运行

## 安装依赖

Ubuntu/Debian：

```bash
sudo apt update

sudo apt install cmake

sudo apt install sqlite3

sudo apt install libsqlite3-dev
```

---

# 编译项目

```bash
mkdir build

cd build

cmake ..

make
```

---

# 运行项目

```bash
./warehouse
```

---

# GitHub

## 克隆项目

```bash
git clone https://github.com/你的用户名/warehouse-management-system.git
```

---

# 项目亮点

## 面向对象设计

项目采用 OOP 思想进行开发：

- Product 类
- Warehouse 类
- User 类
- Logger 类
- Database 类

实现了高内聚、低耦合的软件结构。

---

## 工程化开发

项目采用：

- 多文件结构
- CMake构建
- Git版本管理
- GitHub托管

符合 Linux C++ 工程开发规范。

---

## 数据持久化

使用 SQLite 数据库实现：

- 商品数据存储
- 数据自动加载
- SQL查询

提升了系统可扩展性。

---

## 输入安全与异常处理

系统实现：

- 输入校验
- 非法输入检测
- try-catch异常处理

提升了程序健壮性。

---

# 已实现功能

- [x] 用户登录系统
- [x] 权限控制
- [x] 商品管理
- [x] 库存管理
- [x] 数据统计
- [x] 排序与搜索
- [x] 日志系统
- [x] SQLite数据库
- [x] CMake工程化
- [x] GitHub版本管理

---

# 后续计划

- Qt 图形界面
- Socket 网络版
- 多线程库存管理
- MySQL数据库
- Web后台系统
- REST API
- Docker部署

---

# 开发环境

```text
OS      : Ubuntu Linux
Compiler: g++
CMake   : 3.28.3
SQLite  : 3.45.1
Language: C++17
```

---

# License

MIT License
