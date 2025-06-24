#include "robotlib/scheduler.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>

Scheduler::Scheduler(const std::vector<std::string>& sequence, int dbPort)
    : m_sequence(sequence), m_dbPort(dbPort) {}

void Scheduler::run() {
    DatabaseClient db("127.0.0.1", m_dbPort);
    while (!db.connectToServer()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    for (const auto& line : m_sequence) {
        std::istringstream iss(line);
        std::string comp; std::getline(iss, comp, ':');
        std::string cmd; std::getline(iss, cmd);
        if (!cmd.empty() && cmd[0]==' ') cmd.erase(0,1);
        db.pushCommand(comp, cmd);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
