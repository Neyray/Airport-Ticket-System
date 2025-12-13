#include "../include/Server.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
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