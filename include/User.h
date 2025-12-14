// ==================== User.h ====================
#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User();
    User(const std::string& username, const std::string& password,
         const std::string& realName, const std::string& idCard);
    
    // Getters
    std::string getUsername() const { return username_; }
    std::string getPassword() const { return password_; }
    std::string getRealName() const { return realName_; }
    std::string getIdCard() const { return idCard_; }
    
    // 验证密码
    bool verifyPassword(const std::string& password) const {
        return password_ == password;
    }
    
    // 序列化
    std::string toString() const;
    static User fromString(const std::string& str);

private:
    std::string username_;     // 用户名
    std::string password_;     // 密码
    std::string realName_;     // 真实姓名
    std::string idCard_;       // 身份证号
};

#endif
