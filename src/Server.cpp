#include "../include/Server.h"
#include "../include/Flight.h"
#include "../include/Ticket.h"
#include "../include/User.h"
#include <iostream>
#include <sstream>
#include <ctime>

AirTicketServer::AirTicketServer() {
    db.loadAll();
    setupRoutes();
}

void AirTicketServer::run(int port) {
    // 改为相对于 build/ 目录的路径
    auto ret = svr.set_mount_point("/", "../public");  // ✅
    if (!ret) {
        std::cout << "❌ 错误：找不到 public 文件夹！" << std::endl;
        return;
    }
    
    std::cout << "✅ public 文件夹加载成功" << std::endl;
    std::cout << "🌐 服务器监听端口: " << port << std::endl;
    svr.listen("0.0.0.0", port);
}

void AirTicketServer::setupRoutes() {
    
    // ========== 用户注册 ==========
    svr.Post("/api/register", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 POST /api/register" << std::endl;
        
        // 解析JSON
        size_t pos;
        std::string username, password, realName, idCard;
        
        pos = req.body.find("\"username\":\"") + 12;
        username = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        pos = req.body.find("\"password\":\"") + 12;
        password = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        pos = req.body.find("\"realName\":\"") + 12;
        realName = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        pos = req.body.find("\"idCard\":\"") + 10;
        idCard = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        // 检查用户是否存在
        if (db.findUser(username)) {
            res.status = 400;
            res.set_content("{\"error\":\"用户名已存在\"}", "application/json");
            return;
        }
        
        // 创建用户
        User user(username, password, realName, idCard);
        db.addUser(user);
        
        res.set_content("{\"success\":true,\"message\":\"注册成功\"}", "application/json");
        std::cout << "✅ 用户注册成功: " << username << std::endl;
    });
    
    // ========== 用户登录 ==========
    svr.Post("/api/login", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 POST /api/login" << std::endl;
        
        size_t pos;
        std::string username, password;
        
        pos = req.body.find("\"username\":\"") + 12;
        username = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        pos = req.body.find("\"password\":\"") + 12;
        password = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        User* user = db.findUser(username);
        if (!user || !user->verifyPassword(password)) {
            res.status = 401;
            res.set_content("{\"error\":\"用户名或密码错误\"}", "application/json");
            return;
        }
        
        res.set_content("{\"success\":true,\"message\":\"登录成功\"}", "application/json");
        std::cout << "✅ 用户登录: " << username << std::endl;
    });
    
    // ========== 航班查询（支持筛选） ==========
    svr.Get("/api/flights", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 GET /api/flights" << std::endl;
        
        std::string fromFilter = req.get_param_value("from");
        std::string toFilter = req.get_param_value("to");
        
        auto allFlights = db.getAllFlights();
        std::vector<Flight> filteredFlights;
        
        for (const auto& f : allFlights) {
            bool match = true;
            if (!fromFilter.empty() && f.getFrom().find(fromFilter) == std::string::npos) {
                match = false;
            }
            if (!toFilter.empty() && f.getTo().find(toFilter) == std::string::npos) {
                match = false;
            }
            if (match) {
                filteredFlights.push_back(f);
            }
        }
        
        std::ostringstream json;
        json << "[";
        for (size_t i = 0; i < filteredFlights.size(); ++i) {
            const auto& f = filteredFlights[i];
            json << "{"
                 << "\"id\":\"" << f.getId() << "\","
                 << "\"from\":\"" << f.getFrom() << "\","
                 << "\"to\":\"" << f.getTo() << "\","
                 << "\"price\":" << f.getPrice() << ","
                 << "\"seats\":" << f.getAvailableSeats()
                 << "}";
            if (i < filteredFlights.size() - 1) json << ",";
        }
        json << "]";
        
        res.set_content(json.str(), "application/json");
        std::cout << "✅ 返回 " << filteredFlights.size() << " 条航班" << std::endl;
    });
    
    // ========== 订票 ==========
    svr.Post("/api/book", [this](const httplib::Request& req, httplib::Response& res) {
        std::cout << "📡 POST /api/book" << std::endl;
        
        size_t pos;
        std::string flightId, username;
        
        pos = req.body.find("\"flightId\":\"") + 12;
        flightId = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        pos = req.body.find("\"username\":\"") + 12;
        username = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        Flight* flight = db.findFlight(flightId);
        if (!flight) {
            res.status = 404;
            res.set_content("{\"error\":\"航班不存在\"}", "application/json");
            return;
        }
        
        if (!flight->bookSeat()) {
            res.status = 400;
            res.set_content("{\"error\":\"没有座位了\"}", "application/json");
            return;
        }
        
        std::ostringstream ticketId;
        ticketId << "T" << std::time(nullptr);
        
        Ticket ticket(ticketId.str(), flightId, username, flight->getPrice());
        db.addTicket(ticket);
        db.saveFlights();
        
        std::ostringstream json;
        json << "{\"success\":true,\"ticketId\":\"" << ticketId.str() 
             << "\",\"message\":\"订票成功\"}";
        
        res.set_content(json.str(), "application/json");
        std::cout << "✅ 订票成功: " << ticketId.str() << std::endl;
    });
    
    // ========== 查询订单 ==========
    svr.Get("/api/tickets", [this](const httplib::Request& req, httplib::Response& res) {
        std::string username = req.get_param_value("username");
        if (username.empty()) {
            res.status = 400;
            res.set_content("{\"error\":\"缺少用户名\"}", "application/json");
            return;
        }
        
        auto tickets = db.getUserTickets(username);
        
        std::ostringstream json;
        json << "[";
        for (size_t i = 0; i < tickets.size(); ++i) {
            const auto& t = tickets[i];
            json << "{\"ticketId\":\"" << t.getTicketId() 
                 << "\",\"flightId\":\"" << t.getFlightId() 
                 << "\",\"price\":" << t.getPrice() << "}";
            if (i < tickets.size() - 1) json << ",";
        }
        json << "]";
        
        res.set_content(json.str(), "application/json");
    });
    
    // ========== 退票 ==========
    svr.Post("/api/cancel", [this](const httplib::Request& req, httplib::Response& res) {
        size_t pos = req.body.find("\"ticketId\":\"") + 12;
        std::string ticketId = req.body.substr(pos, req.body.find("\"", pos) - pos);
        
        Ticket* ticket = db.findTicket(ticketId);
        if (!ticket || ticket->isCancelled()) {
            res.status = 404;
            res.set_content("{\"error\":\"订单不存在或已退票\"}", "application/json");
            return;
        }
        
        Flight* flight = db.findFlight(ticket->getFlightId());
        if (flight) {
            flight->cancelSeat();
        }
        
        ticket->cancel();
        db.saveTickets();
        db.saveFlights();
        
        res.set_content("{\"success\":true,\"message\":\"退票成功\"}", "application/json");
        std::cout << "✅ 退票成功: " << ticketId << std::endl;
    });
    
    std::cout << "✅ API 路由注册完成" << std::endl;
}
