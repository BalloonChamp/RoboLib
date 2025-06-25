#include "robotlib/touch_sensor.h"
#include <sstream>

TouchSensor::TouchSensor(const std::string& name, Redis& db)
    : RedisComponent(name, db), m_pressed(false) {}

std::string TouchSensor::handleMessage(const std::string& message) {
    std::istringstream iss(message);
    std::string cmd;
    iss >> cmd;
    if (cmd == "PING") {
        return "ACK SENSOR";
    } else if (cmd == "READ") {
        return std::string("PRESSED ") + (m_pressed ? "1" : "0");
    } else if (cmd == "SET") {
        int v; if (iss >> v) { m_pressed = (v != 0); return "OK"; }
        return "ERR";
    }
    return "UNKNOWN";
}

