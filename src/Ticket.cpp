// ==================== Ticket.cpp ====================
#include "../include/Ticket.h"
#include <sstream>

Ticket::Ticket()
    : ticketId_(""), flightId_(""), username_(""), price_(0), isCancelled_(false) {}

Ticket::Ticket(const std::string& ticketId, const std::string& flightId,
               const std::string& username, int price)
    : ticketId_(ticketId), flightId_(flightId), username_(username), 
      price_(price), isCancelled_(false) {}

std::string Ticket::toString() const {
    std::ostringstream oss;
    oss << ticketId_ << "|" << flightId_ << "|" << username_ << "|" 
        << price_ << "|" << (isCancelled_ ? "1" : "0");
    return oss.str();
}

Ticket Ticket::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string ticketId, flightId, username;
    int price, cancelled;
    char delim;
    
    std::getline(iss, ticketId, '|');
    std::getline(iss, flightId, '|');
    std::getline(iss, username, '|');
    iss >> price >> delim >> cancelled;
    
    Ticket ticket(ticketId, flightId, username, price);
    if (cancelled == 1) {
        ticket.cancel();
    }
    return ticket;
}