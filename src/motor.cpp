#include "robotlib/motor.h"
#include <sstream>

Motor::Motor(const std::string& name, Redis& db, int id)
    : RedisComponent(name, db), m_id(id), m_position(0) {}

std::string Motor::handleMessage(const std::string& message) {
    std::istringstream iss(message);
    std::string cmd;
    iss >> cmd;
    if (cmd == "PING") {
        return "ACK MOTOR " + std::to_string(m_id);
    } else if (cmd == "MOVE") {
        int pos;
        if (iss >> pos) {
            m_position = pos;
            return "OK";
        }
        return "ERR";
    } else if (cmd == "GET") {
        return "POS " + std::to_string(m_position);
    }
    return "UNKNOWN";
}

