#pragma once
#include "Component.h"
#include <nlohmann/json.hpp>

class SchedulerComponent : public Component {
public:
    SchedulerComponent(Database& db, const nlohmann::json& cfg);
    void run() override;
private:
    nlohmann::json m_cfg;
};
