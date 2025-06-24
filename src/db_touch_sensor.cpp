#include "robotlib/db_touch_sensor.h"
#include <sstream>

DbTouchSensor::DbTouchSensor(const std::string& name, int dbPort)
    : DbComponent(name, dbPort), m_pressed(false) {}

std::string DbTouchSensor::handleCommand(const std::string& cmd) {
    std::istringstream iss(cmd); std::string op; iss >> op;
    if (op == "SET") { int v; if (iss >> v) { m_pressed = (v!=0); return "OK"; } return "ERR"; }
    if (op == "READ") { return std::string("PRESSED ") + (m_pressed ? "1" : "0"); }
    return "UNKNOWN";
}

void DbTouchSensor::sendTelemetry(DatabaseClient& db) {
    db.publishTelemetry("Sensor", "pressed", m_pressed ? "1" : "0");
}
