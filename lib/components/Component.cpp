#include "Component.h"

Component::Component(const std::string& name, Database& db)
    : m_name(name), m_db(db) {}

Component::~Component() {
    if (m_thread.joinable()) m_thread.join();
}

void Component::start() {
    m_thread = std::thread([this]{ run(); });
}
