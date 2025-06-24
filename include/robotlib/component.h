#pragma once

#include <string>
#include "robotlib/base_component.h"
#include "robotlib/tcp_server.h"

class Component : public BaseComponent {
public:
    Component(const std::string& name, int port);
    virtual ~Component();
    void run() override;
protected:
    virtual std::string handleMessage(const std::string& message) = 0;
private:
    std::string m_name;
    TcpServer m_server;
};
