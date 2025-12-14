// ==================== Ticket.h ====================
#ifndef TICKET_H
#define TICKET_H

#include <string>

class Ticket {
public:
    Ticket();
    Ticket(const std::string& ticketId, const std::string& flightId,
           const std::string& username, int price);
    
    // Getters
    std::string getTicketId() const { return ticketId_; }
    std::string getFlightId() const { return flightId_; }
    std::string getUsername() const { return username_; }
    int getPrice() const { return price_; }
    bool isCancelled() const { return isCancelled_; }
    
    // 业务方法
    void cancel() { isCancelled_ = true; }
    
    // 序列化
    std::string toString() const;
    static Ticket fromString(const std::string& str);

private:
    std::string ticketId_;     // 订票号
    std::string flightId_;     // 航班号
    std::string username_;     // 用户名
    int price_;                // 票价
    bool isCancelled_;         // 是否已退票
};

#endif