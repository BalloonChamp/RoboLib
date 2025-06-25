#pragma once
#include "Component.h"
#include <mutex>
#include <unordered_map>
#include <string>

// Simple in-process key/value store acting like a mini redis
class Database {
public:
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
private:
    std::mutex m_mutex;
    std::unordered_map<std::string,std::string> m_store;
};

class DatabaseComponent : public Component {
public:
    DatabaseComponent(Database& db);
    void run() override; // does nothing but keep database alive
};
