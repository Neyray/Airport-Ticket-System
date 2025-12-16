#include "../include/Server.h"
#include <iostream>
// 【步骤 1：添加 Windows.h 头文件，用于调用 SetConsoleOutputCP】
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // 【步骤 2：在程序启动时设置控制台输出编码为 UTF-8】
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    
    std::cout << "========================================" << std::endl;
    // 这里的中文和符号现在就能正常显示了
    std::cout << "    ✈️  航空订票系统 - 后端服务器" << std::endl; 
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    AirTicketServer server;
    
    std::cout << "🚀 正在启动服务器..." << std::endl;
    std::cout << "📍 访问地址: http://localhost:8080" << std::endl;
    std::cout << "⚠️  按 Ctrl+C 停止服务器" << std::endl;
    std::cout << std::endl;
    
    server.run(8080);
    
    return 0;
}