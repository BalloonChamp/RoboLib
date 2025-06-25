#include "robotlib/database_server.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>

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
    std::thread printer([this]() {
        while (true) {
            printTelemetry();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    printer.detach();
    while (true) {
        int client = m_server.acceptClient();
        if (client < 0) continue;
        std::thread([this, client]() {
            std::string msg;
            while (m_server.receiveData(client, msg)) {
                std::string reply = handleMessage(msg);
                if (!m_server.sendData(client, reply)) break;
            }
            m_server.closeSocket(client);
        }).detach();
    }
}

std::string DatabaseServer::handleMessage(const std::string& msg) {
    std::istringstream iss(msg);
    std::string cmd; iss >> cmd;
    if (cmd == "PUBLISH") {
        std::string comp, key, value; iss >> comp >> key; std::getline(iss, value);
        if (!value.empty() && value[0]==' ') value.erase(0,1);
        std::lock_guard<std::mutex> lock(m_mutex);
        m_telemetry[comp][key].value = value;
        m_telemetry[comp][key].lastUpdate = std::chrono::steady_clock::now();
        return "OK";
    } else if (cmd == "GET_TELEMETRY") {
        std::string comp, key; iss >> comp >> key;
        std::lock_guard<std::mutex> lock(m_mutex);
        auto itc = m_telemetry.find(comp);
        if (itc != m_telemetry.end()) {
            auto itt = itc->second.find(key);
            if (itt != itc->second.end()) {
                return std::string("VALUE ") + itt->second.value;
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

void DatabaseServer::printTelemetry() {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto now = std::chrono::steady_clock::now();
    std::cout << "\033[2J\033[H"; // clear screen
    std::cout << std::left << std::setw(15) << "Component" << "|"
              << std::setw(12) << "Key" << "|"
              << std::setw(10) << "Value" << "| Age(s)" << std::endl;
    for (const auto& comp : m_telemetry) {
        for (const auto& kv : comp.second) {
            double age = std::chrono::duration_cast<std::chrono::seconds>(now - kv.second.lastUpdate).count();
            std::cout << std::left << std::setw(15) << comp.first << "|"
                      << std::setw(12) << kv.first << "|"
                      << std::setw(10) << kv.second.value << "| " << age << std::endl;
        }
    }
}
