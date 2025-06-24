#pragma once
#include "robotlib/tcp_server.h"
#include <string>
#include <map>
#include <queue>
#include <mutex>
#include <chrono>
#include <thread>
#include <iomanip>

class DatabaseServer {
public:
    DatabaseServer(int port = 6000);
    bool start();
    void run();
private:
    struct TelemetryEntry {
        std::string value;
        std::chrono::steady_clock::time_point lastUpdate;
    };

    std::string handleMessage(const std::string& msg);
    void printTelemetry();
    TcpServer m_server;
    std::mutex m_mutex;
    std::map<std::string, std::map<std::string, TelemetryEntry>> m_telemetry;
    std::map<std::string, std::queue<std::string>> m_commands;
};
