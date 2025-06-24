#pragma once
#include <string>
#include <chrono>
#include <random>
#include <sstream>

class DataPacket {
public:
    DataPacket(const std::string& component,
               const std::string& key,
               const std::string& value = "",
               int intervalMs = 1000);

    std::string uuid() const { return m_uuid; }
    bool shouldUpdate() const;
    void updateTimestamp();

    std::string component;
    std::string key;
    std::string value;

private:
    std::string m_uuid;
    int m_intervalMs;
    std::chrono::steady_clock::time_point m_lastUpdate;
};
