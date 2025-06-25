#include "MotorComponent.h"
#include "DatabaseComponent.h"
#include <chrono>
#include <thread>

MotorComponent::MotorComponent(const std::string& name, int id, Database& db)
    : Component(name, db), m_id(id), m_position(0) {}

void MotorComponent::run() {
    std::string cmdKey = m_name + ":cmd";
    std::string posKey = m_name + ":pos";
    while (true) {
        std::string cmd = m_db.get(cmdKey);
        if (!cmd.empty()) {
            if (cmd.rfind("MOVE",0) == 0) {
                int val = std::stoi(cmd.substr(5));
                m_position = val;
                m_db.set(cmdKey, "");
            }
        }
        m_db.set(posKey, std::to_string(m_position));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
