#pragma once

#include <string>
#include "robotlib/tcp_server.h"

class Component {
public:
    Component(const std::string& name, int port);
    virtual ~Component();
    void run();
protected:
    virtual std::string handleMessage(const std::string& message) = 0;
private:
    std::string m_name;
    TcpServer m_server;
};
