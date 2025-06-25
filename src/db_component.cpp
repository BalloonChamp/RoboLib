#include "robotlib/db_component.h"
#include <chrono>
#include <thread>
#include <iostream>

DbComponent::DbComponent(const std::string& name, int dbPort)
    : m_name(name), m_dbPort(dbPort) {}

void DbComponent::run() {
    DatabaseClient db("127.0.0.1", m_dbPort);
    while (!db.connectToServer()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    while (true) {
        std::string cmd;
        if (db.pollCommand(m_name, cmd) && !cmd.empty()) {
            std::string reply = handleCommand(cmd);
            db.publishTelemetry(m_name, "last_cmd", reply);
        }
        sendTelemetry(db);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
