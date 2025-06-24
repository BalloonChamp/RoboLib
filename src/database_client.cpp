#include "robotlib/database_client.h"
#include <sstream>

DatabaseClient::DatabaseClient(const std::string& host, int port)
    : m_client(host, port) {}

bool DatabaseClient::connectToServer() {
    return m_client.connectToServer();
}

bool DatabaseClient::publishTelemetry(const std::string& component, const std::string& key, const std::string& value) {
    std::string msg = "PUBLISH " + component + " " + key + " " + value;
    return m_client.sendData(msg) && m_client.receiveData(msg);
}

bool DatabaseClient::getTelemetry(const std::string& component, const std::string& key, std::string& value) {
    std::string msg = "GET_TELEMETRY " + component + " " + key;
    if (!m_client.sendData(msg) || !m_client.receiveData(msg)) return false;
    std::istringstream iss(msg);
    std::string status; iss >> status;
    if (status == "VALUE") { std::getline(iss, value); if (!value.empty() && value[0]==' ') value.erase(0,1); return true; }
    return false;
}

bool DatabaseClient::pushCommand(const std::string& component, const std::string& command) {
    std::string msg = "PUSH_CMD " + component + " " + command;
    return m_client.sendData(msg) && m_client.receiveData(msg);
}

bool DatabaseClient::pollCommand(const std::string& component, std::string& command) {
    std::string msg = "POLL_CMD " + component;
    if (!m_client.sendData(msg) || !m_client.receiveData(msg)) return false;
    std::istringstream iss(msg); std::string tag; iss >> tag;
    if (tag == "CMD") { std::getline(iss, command); if(!command.empty() && command[0]==' ') command.erase(0,1); return true; }
    command.clear();
    return true;
}

void DatabaseClient::close() {
    m_client.closeConnection();
}
