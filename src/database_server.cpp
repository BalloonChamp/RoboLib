#include "robotlib/database_server.h"
#include <iostream>
#include <sstream>

DatabaseServer::DatabaseServer(int port) : m_server(port) {}

bool DatabaseServer::start() {
    return m_server.start();
}

void DatabaseServer::run() {
    if (!start()) {
        std::cerr << "Database failed to start\n";
        return;
    }
    std::cout << "Database listening...\n";
    while (true) {
        int client = m_server.acceptClient();
        if (client < 0) continue;
        std::string msg;
        while (m_server.receiveData(client, msg)) {
            std::string reply = handleMessage(msg);
            if (!m_server.sendData(client, reply)) break;
        }
        m_server.closeSocket(client);
    }
}

std::string DatabaseServer::handleMessage(const std::string& msg) {
    std::istringstream iss(msg);
    std::string cmd; iss >> cmd;
    if (cmd == "PUBLISH") {
        std::string comp, key, value; iss >> comp >> key; std::getline(iss, value);
        if (!value.empty() && value[0]==' ') value.erase(0,1);
        std::lock_guard<std::mutex> lock(m_mutex);
        m_telemetry[comp][key] = value;
        return "OK";
    } else if (cmd == "GET_TELEMETRY") {
        std::string comp, key; iss >> comp >> key;
        std::lock_guard<std::mutex> lock(m_mutex);
        auto itc = m_telemetry.find(comp);
        if (itc != m_telemetry.end()) {
            auto itt = itc->second.find(key);
            if (itt != itc->second.end()) {
                return std::string("VALUE ") + itt->second;
            }
        }
        return "NOTFOUND";
    } else if (cmd == "PUSH_CMD") {
        std::string comp; iss >> comp; std::string rest; std::getline(iss, rest);
        if (!rest.empty() && rest[0]==' ') rest.erase(0,1);
        std::lock_guard<std::mutex> lock(m_mutex);
        m_commands[comp].push(rest);
        return "OK";
    } else if (cmd == "POLL_CMD") {
        std::string comp; iss >> comp;
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_commands.find(comp);
        if (it != m_commands.end() && !it->second.empty()) {
            std::string c = it->second.front();
            it->second.pop();
            return std::string("CMD ") + c;
        }
        return "NONE";
    }
    return "ERROR";
}
