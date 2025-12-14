#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include "Flight.h"
#include "Ticket.h"
#include "User.h"

// 前置声明
class Flight;
class Ticket;
class User;

class Database {
public:
    Database();
    
    // 加载和保存所有数据
    void loadAll();
    void saveAll();
    
    // === 航班管理 ===
    void loadFlights();
    void saveFlights();
    std::vector<Flight> getAllFlights() const;
    Flight* findFlight(const std::string& flightId);
    void addFlight(const Flight& flight);
    
    // === 订票管理 ===
    void loadTickets();
    void saveTickets();
    std::vector<Ticket> getUserTickets(const std::string& username) const;
    void addTicket(const Ticket& ticket);
    Ticket* findTicket(const std::string& ticketId);
    
    // === 用户管理 ===
    void loadUsers();
    void saveUsers();
    User* findUser(const std::string& username);
    void addUser(const User& user);

private:
    std::vector<Flight> flights_;
    std::vector<Ticket> tickets_;
    std::vector<User> users_;
};

#endif