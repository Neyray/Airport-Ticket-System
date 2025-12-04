#include "../include/Server.h"
#include <iostream>
#include <string>

AirTicketServer::AirTicketServer() {
    setupRoutes();
}

void AirTicketServer::run(int port) {
    // 告诉服务器，如果浏览器请求 "/"，就返回 public 文件夹里的 index.html
    // set_mount_point 相当于把 public 文件夹暴露给浏览器
    auto ret = svr.set_mount_point("/", "./public"); 
    if (!ret) {
        std::cout << "错误：找不到 public 文件夹！" << std::endl;
    }

    // 启动监听
    svr.listen("0.0.0.0", port);
}

void AirTicketServer::setupRoutes() {
    // API 1: 获取所有航班信息
    // 当浏览器访问 /api/flights 时，执行这个函数
    svr.Get("/api/flights", [this](const httplib::Request& req, httplib::Response& res) {
        
        // --- 模拟：这里应该调用 this->db.getAllFlights() ---
        // 为了演示，我手动拼接一个 JSON 字符串。
        // 在实际项目中，你会遍历你的 flight 列表拼接字符串。
        std::string json_response = "[";
        json_response += "{ \"id\": \"CA1001\", \"from\": \"Beijing\", \"to\": \"Shanghai\", \"price\": 1200 },";
        json_response += "{ \"id\": \"MU2002\", \"from\": \"Guangzhou\", \"to\": \"Beijing\", \"price\": 1500 }";
        json_response += "]";
        // ------------------------------------------------

        // 发回数据，告诉浏览器这是 JSON 格式
        res.set_content(json_response, "application/json");
        std::cout << "收到查询请求，已返回数据。" << std::endl;
    });

    // API 2: 订票 (模拟)
    svr.Post("/api/book", [](const httplib::Request& req, httplib::Response& res) {
        // req.body 里面是前端发来的数据
        std::cout << "收到订票请求: " << req.body << std::endl;
        res.set_content("订票成功", "text/plain");
    });
}