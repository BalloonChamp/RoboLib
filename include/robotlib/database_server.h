#pragma once
#include "robotlib/tcp_server.h"
#include <string>
#include <map>
#include <queue>
#include <mutex>

class DatabaseServer {
public:
    DatabaseServer(int port = 6000);
    bool start();
    void run();
private:
    std::string handleMessage(const std::string& msg);
    TcpServer m_server;
    std::mutex m_mutex;
    std::map<std::string, std::map<std::string, std::string>> m_telemetry;
    std::map<std::string, std::queue<std::string>> m_commands;
};
