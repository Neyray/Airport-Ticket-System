# 📂 项目文件结构说明

本项目采用前后端分离架构，目录结构清晰，便于扩展、维护与阅读。以下为每个目录与文件的作用说明。

---

## 📁 根目录

* **README.md**
  项目的总体介绍、运行方式和使用说明。

* **FILES.md**
  当前文件，用于说明项目的整体目录结构及各部分作用。

---

## 📁 .vscode/ — VS Code 配置目录

存放 VS Code 的项目级配置。

* **tasks.json**

  * 配置 g++ 编译指令
  * 链接 Windows 网络库：`-lws2_32`
  * 添加 Windows 网络宏：`-D_WIN32_WINNT=0x0A00`
  * 自动构建生成 `build/AirTicketSystem.exe`

---

## 📁 public/ — 🌐 前端资源（浏览器可直接访问）

用于存放前端页面与静态资源。

* **index.html** — 前端主页面
  提供页面结构：表格、按钮、输入框等 UI 元素。

* **style.css** — 页面样式
  定义布局、颜色、字体等，让页面更美观。

* **script.js** — 前端交互逻辑

  * 使用 `fetch()` 调用 C++ 后端 API
  * 接收 JSON 数据
  * 动态更新界面内容

---

## 📁 data/ — 🗄️ 数据存储（模拟数据库）

文本文件作为持久化存储，便于调试。

* **flights.txt** — 存储航班数据
* **tickets.txt** — 存储机票订单
* **users.txt** — 存储用户信息

> C++ 后端在启动时会读取这些文件并加载数据结构。

---

## 📁 include/ — 🔧 C++ 头文件（接口层）

存放各模块的 `.h` 文件，声明类与 API。

* **httplib.h**
  Web 服务器核心库，实现 HTTP 请求处理。

* **Server.h**

  * 定义服务器类
  * 指定端口
  * 配置 API 路由（如 `/api/flights`）

* **Database.h**

  * 定义数据库类接口
  * 数据加载、保存、查询等操作

* **Flight.h / Ticket.h / User.h**
  定义核心业务对象的数据结构。

---

## 📁 src/ — ⚙️ C++ 源文件（逻辑实现）

存放 `.cpp` 文件，实施具体功能。

* **main.cpp**
  程序入口：

  ```cpp
  AirTicketServer server;
  server.run();
  ```

* **Server.cpp** — 服务器逻辑实现

  * 实现 `setupRoutes()`
  * 绑定 URL → C++ 函数处理
  * 调用 Database 查询数据
  * 返回 JSON 给前端

* **Database.cpp** — 数据库实现

  * 文件读写
  * 文本与 C++ 对象互相转换
  * 数据持久化

* **Flight.cpp / Ticket.cpp / User.cpp**
  各业务对象的功能实现。

* **UI.cpp** *(已废弃)*

  * 旧的控制台界面实现
  * 已由前端 HTML 页面取代

---
