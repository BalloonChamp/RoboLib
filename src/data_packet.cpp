#include "robotlib/data_packet.h"

DataPacket::DataPacket(const std::string& comp,
                       const std::string& k,
                       const std::string& val,
                       int intervalMs)
    : component(comp), key(k), value(val), m_intervalMs(intervalMs) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::stringstream ss;
    ss << std::hex << mt();
    m_uuid = ss.str();
    m_lastUpdate = std::chrono::steady_clock::now();
}

bool DataPacket::shouldUpdate() const {
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastUpdate).count();
    return diff >= m_intervalMs;
}

void DataPacket::updateTimestamp() {
    m_lastUpdate = std::chrono::steady_clock::now();
}
