#include "robotlib/component.h"
#include <iostream>

Component::Component(const std::string& name, int port)
    : m_name(name), m_server(port) {}

Component::~Component() {}

void Component::run() {
    if (!m_server.start()) {
        std::cerr << m_name << " failed to start server\n";
        return;
    }
    std::cout << m_name << " listening...\n";
    int client = m_server.acceptClient();
    if (client < 0) return;
    std::cout << m_name << " client connected\n";
    std::string msg;
    while (m_server.receiveData(client, msg)) {
        std::string reply = handleMessage(msg);
        if (!m_server.sendData(client, reply)) break;
    }
    m_server.closeSocket(client);
}

