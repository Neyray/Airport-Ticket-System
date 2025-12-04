#ifndef SERVER_H
#define SERVER_H

#include "httplib.h"
#include "Database.h" // 【关键】必须引入这个，编译器才知道 Database 是什么

class AirTicketServer {
public:
    AirTicketServer();
    void run(int port);

private:
    httplib::Server svr;
    Database db; // 现在编译器认识 Database 了

    void setupRoutes();
};

#endif