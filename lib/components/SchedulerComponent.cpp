#include "SchedulerComponent.h"
#include "DatabaseComponent.h"
#include <chrono>
#include <thread>

SchedulerComponent::SchedulerComponent(Database& db, const nlohmann::json& cfg)
    : Component("scheduler", db), m_cfg(cfg) {}

void SchedulerComponent::run() {
    if (!m_cfg.contains("commands")) return;
    for (auto& cmd : m_cfg["commands"]) {
        int delay = cmd.value("delay_ms", 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        std::string key = cmd["target"].get<std::string>() + ":cmd";
        std::string val = cmd["command"].get<std::string>();
        m_db.set(key, val);
    }
}
