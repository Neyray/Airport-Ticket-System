#include <iostream>
#include "../include/Server.h" // 引用我们将要写的Server类

int main() {
    std::cout << "正在启动航空订票系统服务器..." << std::endl;
    std::cout << "请在浏览器访问: http://localhost:8080" << std::endl;

    // 实例化服务器对象并启动
    AirTicketServer server;
    server.run(8080); // 监听 8080 端口

    return 0;
}