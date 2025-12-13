#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

class Flight {
public:
    Flight();
    Flight(const std::string& id, const std::string& from, 
           const std::string& to, int price, int seats);
    
    // Getters
    std::string getId() const { return id_; }
    std::string getFrom() const { return from_; }
    std::string getTo() const { return to_; }
    int getPrice() const { return price_; }
    int getAvailableSeats() const { return availableSeats_; }
    
    // Setters
    void setPrice(int price) { price_ = price; }
    void setAvailableSeats(int seats) { availableSeats_ = seats; }
    
    // 业务方法
    bool bookSeat();  // 订座
    bool cancelSeat(); // 退座
    
    // 序列化
    std::string toString() const;
    static Flight fromString(const std::string& str);

private:
    std::string id_;           // 航班号
    std::string from_;         // 出发地
    std::string to_;           // 目的地
    int price_;                // 价格
    int availableSeats_;       // 剩余座位数
};

#endif