#include "../include/Database.h"
#include "../include/Flight.h"
#include "../include/Ticket.h"
#include "../include/User.h"
#include <iostream>
#include <fstream>
#include <sstream>

Database::Database() {
    std::cout << "[Database] 数据库对象已创建" << std::endl;
}

// 加载所有数据
void Database::loadAll() {
    loadFlights();
    loadTickets();
    loadUsers();
}

// 保存所有数据
void Database::saveAll() {
    saveFlights();
    saveTickets();
    saveUsers();
}

// === 航班管理 ===
void Database::loadFlights() {
    flights_.clear();
    std::ifstream file("data/flights.txt");
    if (!file.is_open()) {
        std::cout << "[Database] 无法打开 flights.txt" << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#') {
            flights_.push_back(Flight::fromString(line));
        }
    }
    file.close();
    std::cout << "[Database] 已加载 " << flights_.size() << " 条航班数据" << std::endl;
}

void Database::saveFlights() {
    std::ofstream file("data/flights.txt");
    if (!file.is_open()) return;
    
    for (const auto& flight : flights_) {
        file << flight.toString() << "\n";
    }
    file.close();
}

std::vector<Flight> Database::getAllFlights() const {
    return flights_;
}

Flight* Database::findFlight(const std::string& flightId) {
    for (auto& flight : flights_) {
        if (flight.getId() == flightId) {
            return &flight;
        }
    }
    return nullptr;
}

void Database::addFlight(const Flight& flight) {
    flights_.push_back(flight);
    saveFlights();
}

// === 订票管理 ===
void Database::loadTickets() {
    tickets_.clear();
    std::ifstream file("data/tickets.txt");
    if (!file.is_open()) return;
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#') {
            tickets_.push_back(Ticket::fromString(line));
        }
    }
    file.close();
}

void Database::saveTickets() {
    std::ofstream file("data/tickets.txt");
    if (!file.is_open()) return;
    
    for (const auto& ticket : tickets_) {
        file << ticket.toString() << "\n";
    }
    file.close();
}

std::vector<Ticket> Database::getUserTickets(const std::string& username) const {
    std::vector<Ticket> result;
    for (const auto& ticket : tickets_) {
        if (ticket.getUsername() == username && !ticket.isCancelled()) {
            result.push_back(ticket);
        }
    }
    return result;
}

void Database::addTicket(const Ticket& ticket) {
    tickets_.push_back(ticket);
    saveTickets();
}

Ticket* Database::findTicket(const std::string& ticketId) {
    for (auto& ticket : tickets_) {
        if (ticket.getTicketId() == ticketId) {
            return &ticket;
        }
    }
    return nullptr;
}

// === 用户管理 ===
void Database::loadUsers() {
    users_.clear();
    std::ifstream file("data/users.txt");
    if (!file.is_open()) return;
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#') {
            users_.push_back(User::fromString(line));
        }
    }
    file.close();
}

void Database::saveUsers() {
    std::ofstream file("data/users.txt");
    if (!file.is_open()) return;
    
    for (const auto& user : users_) {
        file << user.toString() << "\n";
    }
    file.close();
}

User* Database::findUser(const std::string& username) {
    for (auto& user : users_) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

void Database::addUser(const User& user) {
    users_.push_back(user);
    saveUsers();
}