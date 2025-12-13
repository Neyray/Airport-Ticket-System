#include "../include/Server.h"
#include "../include/Flight.h"
#include "../include/Ticket.h"
#include "../include/User.h"
#include <iostream>
#include <sstream>
#include <ctime>

AirTicketServer::AirTicketServer() {
    // 启动时加载数据
    db.loadAll();
    setupRoutes();
}

void AirTicketServer::run(int port) {
    // 挂载静态文件目录
    auto ret = svr.set_mount_point("/", "./public");
    if (!ret) {
        std::cout << "❌ 错误：找不到 public 文件夹！" << std::endl;
        return;
    }
    
    std::cout << "✅ public 文件夹加载成功" << std::endl;
    std::cout << "🌐 服务器监听端口: " << port << std::endl;
    
    // 启动服务器
    svr.listen("0.0.0.0", port);
}

void AirTicketServer::setupRoutes() {
    
    // ========== API 1: 查询所有航班 ==========
    svr.Get("/api/flights", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 收到请求: GET /api/flights" << std::endl;
        
        auto flights = db.getAllFlights();
        
        // 构建 JSON 响应
        std::ostringstream json;
        json << "[";
        for (size_t i = 0; i < flights.size(); ++i) {
            const auto& f = flights[i];
            json << "{"
                 << "\"id\":\"" << f.getId() << "\","
                 << "\"from\":\"" << f.getFrom() << "\","
                 << "\"to\":\"" << f.getTo() << "\","
                 << "\"price\":" << f.getPrice() << ","
                 << "\"seats\":" << f.getAvailableSeats()
                 << "}";
            if (i < flights.size() - 1) json << ",";
        }
        json << "]";
        
        res.set_content(json.str(), "application/json");
        std::cout << "✅ 返回 " << flights.size() << " 条航班数据" << std::endl;
    });
    
    // ========== API 2: 订票 ==========
    svr.Post("/api/book", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 收到请求: POST /api/book" << std::endl;
        std::cout << "📦 请求体: " << req.body << std::endl;
        
        // 简单解析 JSON (手动方式)
        // 实际项目建议使用 nlohmann/json 库
        std::string flightId, username;
        
        // 提取 flightId
        size_t pos1 = req.body.find("\"flightId\":\"") + 12;
        size_t pos2 = req.body.find("\"", pos1);
        flightId = req.body.substr(pos1, pos2 - pos1);
        
        // 提取 username
        pos1 = req.body.find("\"username\":\"") + 12;
        pos2 = req.body.find("\"", pos1);
        username = req.body.substr(pos1, pos2 - pos1);
        
        // 查找航班
        Flight* flight = db.findFlight(flightId);
        if (!flight) {
            res.status = 404;
            res.set_content("{\"error\":\"航班不存在\"}", "application/json");
            std::cout << "❌ 航班不存在: " << flightId << std::endl;
            return;
        }
        
        // 尝试订座
        if (!flight->bookSeat()) {
            res.status = 400;
            res.set_content("{\"error\":\"没有座位了\"}", "application/json");
            std::cout << "❌ 订座失败：无座位" << std::endl;
            return;
        }
        
        // 生成订票号
        std::ostringstream ticketId;
        ticketId << "T" << std::time(nullptr);
        
        // 创建订票记录
        Ticket ticket(ticketId.str(), flightId, username, flight->getPrice());
        db.addTicket(ticket);
        db.saveFlights(); // 保存航班座位变化
        
        // 返回成功
        std::ostringstream json;
        json << "{"
             << "\"success\":true,"
             << "\"ticketId\":\"" << ticketId.str() << "\","
             << "\"message\":\"订票成功\""
             << "}";
        
        res.set_content(json.str(), "application/json");
        std::cout << "✅ 订票成功: " << ticketId.str() << std::endl;
    });
    
    // ========== API 3: 查询我的订单 ==========
    svr.Get("/api/tickets", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 收到请求: GET /api/tickets" << std::endl;
        
        // 从查询参数获取用户名
        std::string username = req.get_param_value("username");
        if (username.empty()) {
            res.status = 400;
            res.set_content("{\"error\":\"缺少用户名\"}", "application/json");
            return;
        }
        
        auto tickets = db.getUserTickets(username);
        
        // 构建 JSON
        std::ostringstream json;
        json << "[";
        for (size_t i = 0; i < tickets.size(); ++i) {
            const auto& t = tickets[i];
            json << "{"
                 << "\"ticketId\":\"" << t.getTicketId() << "\","
                 << "\"flightId\":\"" << t.getFlightId() << "\","
                 << "\"price\":" << t.getPrice()
                 << "}";
            if (i < tickets.size() - 1) json << ",";
        }
        json << "]";
        
        res.set_content(json.str(), "application/json");
        std::cout << "✅ 返回 " << tickets.size() << " 张票" << std::endl;
    });
    
    // ========== API 4: 退票 ==========
    svr.Post("/api/cancel", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 收到请求: POST /api/cancel" << std::endl;
        
        // 提取 ticketId
        size_t pos1 = req.body.find("\"ticketId\":\"") + 12;
        size_t pos2 = req.body.find("\"", pos1);
        std::string ticketId = req.body.substr(pos1, pos2 - pos1);
        
        Ticket* ticket = db.findTicket(ticketId);
        if (!ticket || ticket->isCancelled()) {
            res.status = 404;
            res.set_content("{\"error\":\"订单不存在或已退票\"}", "application/json");
            return;
        }
        
        // 退座
        Flight* flight = db.findFlight(ticket->getFlightId());
        if (flight) {
            flight->cancelSeat();
        }
        
        // 标记为已退票
        ticket->cancel();
        db.saveTickets();
        db.saveFlights();
        
        res.set_content("{\"success\":true,\"message\":\"退票成功\"}", "application/json");
        std::cout << "✅ 退票成功: " << ticketId << std::endl;
    });
    
    std::cout << "✅ API 路由注册完成" << std::endl;
}