#pragma once
#include <string>
#include <thread>

class Database; // forward

class Component {
public:
    Component(const std::string& name, Database& db);
    virtual ~Component();
    virtual void start();
    virtual void run() = 0;
protected:
    std::string m_name;
    Database& m_db;
    std::thread m_thread;
};
