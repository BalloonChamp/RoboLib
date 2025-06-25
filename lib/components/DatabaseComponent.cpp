#include <chrono>
#include <thread>
#include "DatabaseComponent.h"

void Database::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_store[key] = value;
}

std::string Database::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_store.find(key);
    if (it == m_store.end()) return "";
    return it->second;
}

DatabaseComponent::DatabaseComponent(Database& db)
    : Component("database", db) {}

void DatabaseComponent::run() {
    // database lives until program exit
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
