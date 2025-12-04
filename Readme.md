# ✈️ 航空订票系统 (Air Ticket System)

一个基于 **C++ 后端** 与 **HTML/JS 前端** 的前后端分离架构项目。
后端负责核心逻辑与数据处理，前端负责界面展示与用户交互。

---

## 🛠️ 技术栈

### **后端**

* C++17
* Web 服务器：`cpp-httplib`（头文件库）
* 编译器：MinGW (g++)
* 开发工具：VS Code

### **前端**

* HTML5
* CSS3
* JavaScript（原生，无框架）

---

## 🚀 如何运行

### **1. 编译**

在 VS Code 中按下：

```
Ctrl + Shift + B
```

确保 `.vscode/tasks.json` 中包含：

```
-D_WIN32_WINNT=0x0A00
```

编译成功后，生成文件位于：

```
build/AirTicketSystem.exe
```

---

### **2. 启动服务器**

在终端运行：

```bash
./build/AirTicketSystem.exe
```

---

### **3. 访问系统**

保持终端运行，打开浏览器并访问：

👉 [http://localhost:8080](http://localhost:8080)

---

## ✨ 功能特性（开发中）

| 功能        |  状态 |
| --------- | :-: |
| Web 服务器搭建 |  ✔️ |
| 航班查询      |  ⏳  |
| 机票预订      |  ⏳  |
| 用户登录/注册   |  ⏳  |
| 退票改签      |  ⏳  |

---


