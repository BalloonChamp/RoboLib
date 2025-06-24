#pragma once
#include "robotlib/tcp_client.h"
#include <string>

class DatabaseClient {
public:
    DatabaseClient(const std::string& host = "127.0.0.1", int port = 6000);
    bool connectToServer();
    bool publishTelemetry(const std::string& component, const std::string& key, const std::string& value);
    bool getTelemetry(const std::string& component, const std::string& key, std::string& value);
    bool pushCommand(const std::string& component, const std::string& command);
    bool pollCommand(const std::string& component, std::string& command);
    void close();
private:
    TcpClient m_client;
};
