// ==================== Flight.cpp ====================
#include "../include/Flight.h"
#include <sstream>

Flight::Flight() 
    : id_(""), from_(""), to_(""), price_(0), availableSeats_(0) {}

Flight::Flight(const std::string& id, const std::string& from, 
               const std::string& to, int price, int seats)
    : id_(id), from_(from), to_(to), price_(price), availableSeats_(seats) {}

bool Flight::bookSeat() {
    if (availableSeats_ > 0) {
        availableSeats_--;
        return true;
    }
    return false;
}

bool Flight::cancelSeat() {
    availableSeats_++;
    return true;
}

std::string Flight::toString() const {
    std::ostringstream oss;
    oss << id_ << "|" << from_ << "|" << to_ << "|" 
        << price_ << "|" << availableSeats_;
    return oss.str();
}

Flight Flight::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string id, from, to;
    int price, seats;
    char delim;
    
    std::getline(iss, id, '|');
    std::getline(iss, from, '|');
    std::getline(iss, to, '|');
    iss >> price >> delim >> seats;
    
    return Flight(id, from, to, price, seats);
}