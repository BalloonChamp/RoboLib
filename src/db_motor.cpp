#include "robotlib/db_motor.h"
#include <sstream>

DbMotor::DbMotor(const std::string& name, int id, int dbPort)
    : DbComponent(name, dbPort), m_id(id), m_position(0) {}

std::string DbMotor::handleCommand(const std::string& cmd) {
    std::istringstream iss(cmd); std::string op; iss >> op;
    if (op == "MOVE") { int pos; if (iss >> pos) { m_position = pos; return "OK"; } return "ERR"; }
    if (op == "GET") { return "POS " + std::to_string(m_position); }
    return "UNKNOWN";
}

void DbMotor::sendTelemetry(DatabaseClient& db) {
    db.publishTelemetry("Motor" + std::to_string(m_id), "position", std::to_string(m_position));
}
