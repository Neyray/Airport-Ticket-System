# ✈️ 航空订票系统 (Air Ticket Booking System)

一个基于 **C++ 后端** 与 **HTML/JS 前端** 的前后端分离架构项目。后端使用 cpp-httplib 实现 RESTful API 服务器，前端提供现代化的 Web 界面，支持用户注册、登录、航班查询、订票和退票等完整功能。

---

## 🛠️ 技术栈

### **后端**
- **语言**：C++17
- **Web 框架**：cpp-httplib v0.28.0（单头文件 HTTP 库）
- **数据存储**：文本文件（模拟数据库）
- **编译器**：MinGW (g++ 8.1.0 或更高版本)
- **开发工具**：Visual Studio Code

### **前端**
- **HTML5** - 页面结构
- **CSS3** - 渐变背景、响应式设计、现代化 UI
- **JavaScript (ES6+)** - Fetch API、异步请求处理

---

## 🌟 核心功能

### ✅ 已实现功能

| 功能模块 | 描述 | 状态 |
|---------|------|------|
| 🔐 **用户系统** | 用户注册、登录、身份验证 | ✔️ 完成 |
| 🔍 **航班查询** | 支持按出发地/目的地筛选、显示所有航班 | ✔️ 完成 |
| 🎫 **订票功能** | 实时座位检查、自动生成订票号 | ✔️ 完成 |
| 📋 **订单管理** | 查看个人订单列表、订单详情 | ✔️ 完成 |
| ❌ **退票服务** | 订票号验证、座位释放、数据同步 | ✔️ 完成 |
| 💾 **数据持久化** | 文本文件存储、自动加载保存 | ✔️ 完成 |
| 🌐 **Web 服务器** | RESTful API、静态文件托管 | ✔️ 完成 |

### 🎨 界面特点
- 🌈 **渐变背景**：紫色渐变配色，视觉效果出众
- 📱 **响应式设计**：自适应不同屏幕尺寸
- 🎭 **动画效果**：按钮悬停、表单聚焦动画
- 🔔 **实时反馈**：操作成功/失败的即时提示
- 🎯 **用户友好**：直观的操作流程，清晰的信息展示

---

## 🚀 快速开始

### **环境要求**
- Windows 10/11（其他系统需修改部分代码）
- MinGW-w64（g++ 8.1.0+）
- Visual Studio Code（推荐）
- 现代浏览器（Chrome、Edge、Firefox）

### **1️⃣ 克隆项目**
```bash
git clone <repository-url>
cd AirTicketSystem
```

### **2️⃣ 编译项目**

**方式一：使用 VS Code**
```
按 Ctrl + Shift + B
选择 "C/C++: g++.exe build active file"
```

**方式二：使用命令行**
```bash
g++ -std=c++17 ^
    -D_WIN32_WINNT=0x0A00 ^
    -o build/AirTicketSystem.exe ^
    src/*.cpp ^
    -lws2_32
```

### **3️⃣ 运行服务器**
```bash
cd build
./AirTicketSystem.exe
```

**成功启动后会看到：**
```
========================================
    ✈️  航空订票系统 - 后端服务器
========================================

✅ public 文件夹加载成功
🌐 服务器监听端口: 8080
🚀 正在启动服务器...
📍 访问地址: http://localhost:8080
⚠️  按 Ctrl+C 停止服务器
```

### **4️⃣ 访问系统**
打开浏览器访问：  
👉 **http://localhost:8080**

---

## 📡 API 接口说明

### 用户相关

#### 注册用户
```http
POST /api/register
Content-Type: application/json

{
  "username": "testuser",
  "password": "123456",
  "realName": "张三",
  "idCard": "110101199001011234"
}
```

#### 用户登录
```http
POST /api/login
Content-Type: application/json

{
  "username": "testuser",
  "password": "123456"
}
```

### 航班相关

#### 查询所有航班
```http
GET /api/flights
```

#### 按条件筛选航班
```http
GET /api/flights?from=北京&to=上海
```

**响应示例：**
```json
[
  {
    "id": "CA1001",
    "from": "北京",
    "to": "上海",
    "price": 800,
    "seats": 50
  }
]
```

### 订票相关

#### 订票
```http
POST /api/book
Content-Type: application/json

{
  "flightId": "CA1001",
  "username": "testuser"
}
```

**响应示例：**
```json
{
  "success": true,
  "ticketId": "T1734567890",
  "message": "订票成功"
}
```

#### 查询个人订单
```http
GET /api/tickets?username=testuser
```

#### 退票
```http
POST /api/cancel
Content-Type: application/json

{
  "ticketId": "T1734567890"
}
```

---

## 📂 项目结构
```
AirTicketSystem/
├── .vscode/           # VS Code 配置
│   └── tasks.json     # 编译任务配置
├── include/           # C++ 头文件
│   ├── httplib.h      # Web 服务器库
│   ├── Server.h       # 服务器类声明
│   ├── Database.h     # 数据库类声明
│   ├── Flight.h       # 航班类声明
│   ├── Ticket.h       # 订票类声明
│   └── User.h         # 用户类声明
├── src/               # C++ 源文件
│   ├── main.cpp       # 程序入口
│   ├── Server.cpp     # 服务器实现
│   ├── Database.cpp   # 数据库实现
│   ├── Flight.cpp     # 航班类实现
│   ├── Ticket.cpp     # 订票类实现
│   └── User.cpp       # 用户类实现
├── public/            # 前端资源
│   └── index.html     # 主页面（含 CSS/JS）
├── data/              # 数据文件
│   ├── flights.txt    # 航班数据
│   ├── tickets.txt    # 订票记录
│   └── users.txt      # 用户信息
├── build/             # 编译输出
│   └── AirTicketSystem.exe
├── README.md          # 项目说明（本文件）
└── FILES.md           # 文件结构详解
```

---

## 🗄️ 数据格式说明

### flights.txt（航班数据）
```
# 格式：航班号|出发地|目的地|价格|剩余座位数
CA1001|北京|上海|800|50
MU2002|上海|广州|600|30
```

### tickets.txt（订票记录）
```
# 格式：订票号|航班号|用户名|价格|是否已退票(0/1)
T1734567890|CA1001|testuser|800|0
T1734567891|MU2002|testuser|600|1
```

### users.txt（用户信息）
```
# 格式：用户名|密码|真实姓名|身份证号
testuser|123456|张三|110101199001011234
admin|admin123|管理员|110101199001011235
```

---

## 🎮 使用指南

### 1️⃣ 注册/登录
- 首次访问需要注册账号
- 点击"注册"按钮，填写完整信息
- 注册成功后返回登录界面

### 2️⃣ 查询航班
- 登录后自动显示所有航班
- 使用搜索框按出发地/目的地筛选
- 点击"显示全部"返回完整列表

### 3️⃣ 订票
- 在航班列表中找到目标航班
- 点击"订票"按钮
- 确认后自动生成订票号

### 4️⃣ 查看订单
- 点击"我的订单"按钮
- 弹窗显示所有订票记录

### 5️⃣ 退票
- 点击"退票"按钮
- 输入订票号
- 确认后自动释放座位

---

## 🔧 常见问题

### Q1: 编译失败，提示找不到 `ws2_32`？
**A:** 确保使用 MinGW-w64，并在编译命令中添加 `-lws2_32`。

### Q2: 运行后浏览器显示 404？
**A:** 检查是否在 `build/` 目录下运行程序，且 `public/` 文件夹存在。

### Q3: 登录后看不到航班数据？
**A:** 检查 `data/flights.txt` 是否存在且格式正确。

### Q4: 修改数据文件后不生效？
**A:** 需要重启服务器（Ctrl+C 停止后重新运行）。

### Q5: 控制台中文乱码？
**A:** 程序已通过 `SetConsoleOutputCP(65001)` 设置 UTF-8 编码，确保终端支持 UTF-8。

---

## 🚀 未来扩展方向

- [ ] 添加管理员后台（航班管理、用户管理）
- [ ] 实现座位选择功能（可视化座位图）
- [ ] 引入真实数据库（SQLite/MySQL）
- [ ] 支持航班搜索的更多条件（日期、时间、价格区间）
- [ ] 实现支付功能模拟
- [ ] 添加用户头像、个人信息修改
- [ ] 实现航班动态（延误、取消通知）
- [ ] 支持多语言界面（中文/英文切换）

---

## 📄 开源协议

本项目采用 MIT 协议开源。

---

## 👥 贡献指南

欢迎提交 Issue 和 Pull Request！

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 提交 Pull Request

---

## 📞 联系方式

如有问题或建议，欢迎通过以下方式联系：

- 📧 Email: [your-email@example.com]
- 💬 Issue: [GitHub Issues]

---

## 🙏 致谢

- [cpp-httplib](https://github.com/yhirose/cpp-httplib) - 优秀的 C++ HTTP 库
- [MinGW-w64](http://mingw-w64.org/) - Windows 平台 GCC 工具链
- [Visual Studio Code](https://code.visualstudio.com/) - 强大的代码编辑器

---

**🎉 感谢使用航空订票系统！**