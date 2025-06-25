#include "robotlib/database_component.h"
#include <cstdlib>

DatabaseComponent::DatabaseComponent(int port) : m_port(port) {}

void DatabaseComponent::run() {
    std::string cmd = "redis-server --port " + std::to_string(m_port);
    system(cmd.c_str());
}
