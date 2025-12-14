// ==================== User.cpp ====================
#include "../include/User.h"
#include <sstream>

User::User()
    : username_(""), password_(""), realName_(""), idCard_("") {}

User::User(const std::string& username, const std::string& password,
           const std::string& realName, const std::string& idCard)
    : username_(username), password_(password), 
      realName_(realName), idCard_(idCard) {}

std::string User::toString() const {
    std::ostringstream oss;
    oss << username_ << "|" << password_ << "|" 
        << realName_ << "|" << idCard_;
    return oss.str();
}

User User::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string username, password, realName, idCard;
    
    std::getline(iss, username, '|');
    std::getline(iss, password, '|');
    std::getline(iss, realName, '|');
    std::getline(iss, idCard, '|');
    
    return User(username, password, realName, idCard);
}